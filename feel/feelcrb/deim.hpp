/* -*- mode: c++; coding: utf-8; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4; show-trailing-whitespace: t -*-

  This file is part of the Feel library

  Author(s): Christophe Prud'homme <christophe.prudhomme@feelpp.org>
       Date: 2012-05-02

  Copyright (C) 2012 Université Joseph Fourier (Grenoble I)

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/
/**
   \file deim.hpp
   \author JB Wahl
   \date 2017-01-27
 */
#ifndef _FEELPP_DEIM_HPP
#define _FEELPP_DEIM_HPP 1

#include <limits>
#include <numeric>
#include <string>
#include <iostream>
#include <fstream>

#include <boost/ref.hpp>
#include <boost/next_prior.hpp>
#include <boost/type_traits.hpp>
#include <boost/tuple/tuple.hpp>

#include <feel/feelcrb/parameterspace.hpp>
#include <feel/feelvf/vf.hpp>
#include <Eigen/Core>

namespace Feel
{


template <typename ModelType>
class DEIM
{

public :
    typedef ModelType model_type;
    typedef boost::shared_ptr<model_type> model_ptrtype;


    typedef typename ModelType::parameterspace_type parameterspace_type;
    typedef typename ModelType::parameterspace_ptrtype parameterspace_ptrtype;
    typedef typename ModelType::parameter_type parameter_type;
    typedef typename parameterspace_type::sampling_type sampling_type;
    typedef typename parameterspace_type::sampling_ptrtype sampling_ptrtype;

    typedef typename ModelType::value_type value_type;
    typedef Backend<value_type> backend_type;
    typedef boost::shared_ptr<backend_type> backend_ptrtype;

    typedef typename backend_type::vector_type vector_type;
    typedef typename backend_type::vector_ptrtype vector_ptrtype;

    typedef std::function<vector_ptrtype ( const parameter_type& mu)> assemble_function_type;

    typedef Eigen::MatrixXd matrixN_type;
    typedef Eigen::VectorXd vectorN_type;

    typedef boost::tuple<double,int> vectormax_type;
    typedef boost::tuple<parameter_type,double> bestfit_type;

    DEIM()
    {}

    DEIM( parameterspace_ptrtype Dmu, sampling_ptrtype sampling=NULL ) :
        M_parameter_space( Dmu ),
        M_trainset( sampling ),
        M_M(0),
        M_tol(1e-8)
    {
        if ( !M_trainset )
            M_trainset = Dmu->sampling();
        if ( M_trainset->empty() )
        {
            int sampling_size = ioption(_name="eim.sampling-size");
            std::string file_name = ( boost::format("eim_trainset_%1%") % sampling_size ).str();
            bool all_procs_have_same_sampling=true;
            std::string sampling_mode = "log-equidistribute";// random, log-random, log-equidistribute, equidistribute
            std::ifstream file ( file_name );
            if( ! file )
            {
                M_trainset->sample( sampling_size, sampling_mode, all_procs_have_same_sampling, file_name );
            }
            else
            {
                M_trainset->clear();
                M_trainset->readFromFile(file_name);
            }
            Feel::cout << "DEIM sampling created with " << sampling_size << " points.\n";
        }
    }

    void run()
    {
        int mMax = ioption("eim.dimension-max");
        auto mu = M_parameter_space->max();

        vector_ptrtype V = assemble( mu );

        // first interpolation point
        auto vec_max = vectorMaxAbs( V );
        int i = vec_max.template get<1>();
        double max = vec_max.template get<0>();

        M_M=1;

        // first vector of the base
        V->scale( 1./max );
        M_bases.push_back( V );

        M_index.push_back(i);

        M_B.conservativeResize(M_M,M_M);
        M_B(M_M-1,M_M-1) = V->operator()(i);


        tic();
        for ( ; M_M<=mMax; )
        {
            auto best_fit = computeBestFit();
            Feel::cout << "DEIM : Current error : "<< best_fit.template get<1>()
                       <<", tolerance : " << M_tol <<std::endl;
            if ( best_fit.template get<1>()<M_tol )
            {
                Feel::cout << "Stopping greedy algorithm\n";
                break;
            }

            mu = best_fit.template get<0>();

            vector_ptrtype newV = assemble(mu);
            vectorN_type coeff = computeCoefficient( newV );


            // Assemble Residual
            for ( int i=0; i<M_M; i++ )
                newV->add( -coeff(i), M_bases[i] );

            vec_max = vectorMaxAbs( newV );

            M_M++;
            max = vec_max.template get<0>();
            newV->scale( 1./max );
            M_bases.push_back( newV );

            i = vec_max.template get<1>();
            M_index.push_back(i);

            M_B.conservativeResize( M_M, M_M );
            // update last row of M_B
            for ( int j = 0; j<M_M; j++ )
            {
                M_B(M_M-1, j) = M_bases[j]->operator() (M_index[M_M-1] );
            }
            //update last col of M_B
            for ( int i=0; i<M_M; i++ )
            {
                M_B(i, M_M-1) = M_bases[M_M-1]->operator() (M_index[i]);
            }
        }
        toc("DEIM : greedy");
        Feel::cout << "DEIM number of basis function vector : "<< M_M << std::endl;
    }

    assemble_function_type assemble;

    vectorN_type beta( parameter_type mu )
    {
        return computeCoefficient( mu );
    }

    std::vector<vector_ptrtype> q()
    {
        return M_bases;
    }

    int size()
    {
        return M_M;
    }

private :
    vectormax_type vectorMaxAbs( vector_ptrtype V )
    {
        auto newV = V->clone();
        *newV = *V;
        newV->abs();
        int index = 0;
        double max = newV->maxWithIndex( &index );
        return boost::make_tuple( max, index );
    }

    bestfit_type computeBestFit()
    {
        tic();
        double max=0;
        auto mu_max = M_parameter_space->element();
        for ( auto const& mu : *M_trainset )
        {
            vector_ptrtype V = assemble( mu );
            vectorN_type coeff = computeCoefficient( V );

            for ( int i=0; i<M_M; i++ )
            {
                V->add( -coeff(i), M_bases[i] );
            }

            double norm = V->linftyNorm();
            if ( norm>max )
            {
                max = norm;
                mu_max = mu;
            }
        }
        toc("DEIM : compute best fit");

        return boost::make_tuple( mu_max, max );
    }

    vectorN_type computeCoefficient( parameter_type mu )
    {
        vector_ptrtype V = assemble( mu );
        return computeCoefficient( V );
    }

    vectorN_type computeCoefficient( vector_ptrtype V )
    {
        vectorN_type rhs (M_M);
        for ( int i=0; i<M_M; i++ )
        {
            rhs(i) = V->operator() ( M_index[i] );
        }
        vectorN_type coeff (M_M);
        coeff = M_B.lu().solve( rhs );
        return coeff;
    }

    parameterspace_ptrtype M_parameter_space;
    sampling_ptrtype M_trainset;
    int M_M;
    double M_tol;
    std::vector<int> M_index;
    matrixN_type M_B;
    std::vector< vector_ptrtype > M_bases;


};



}

#endif