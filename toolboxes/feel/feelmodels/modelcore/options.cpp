/* -*- mode: c++; coding: utf-8; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4; show-trailing-whitespace: t -*- vim:fenc=utf-8:ft=cpp:et:sw=4:ts=4:sts=4

  This file is part of the Feel library

  Author(s): Vincent Chabannes <vincent.chabannes@feelpp.org>
       Date: 2011-08-01

  Copyright (C) 2011 Universite Joseph Fourier (Grenoble I)

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 3.0 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include <feel/feelmodels/modelcore/options.hpp>
#include <feel/feelmodels/modelcore/feelmodelscoreconstconfig.hpp>
#include <feel/feelcore/feel.hpp>

namespace Feel
{

Feel::po::options_description envfeelmodels_options(std::string const& prefix)
{
    Feel::po::options_description envfsiOptions("Env FSI options");
    envfsiOptions.add_options()
        (prefixvm(prefix,"verbose").c_str(), Feel::po::value<bool>()->default_value( true ), "true or false to view verbose")
        (prefixvm(prefix,"evalpt-path").c_str(), Feel::po::value< std::string >(), "path of file containing set of point to evaluate")
        (prefixvm(prefix,"comm.useNonStandartCompositeSpace").c_str(), Feel::po::value< bool >()->default_value( false ), "try old build of composite space")
        (prefixvm(prefix,"rebuildOnlyAMeshPartion").c_str(), Feel::po::value< bool >()->default_value( false ), "only rebuild a mesh partition")
        ;
    envfsiOptions.add( Feel::gmsh_options("meshpartitioning") );
    envfsiOptions.add_options()
        (prefixvm(prefix,"meshpartitioning.gmsh.outputfilename").c_str(), Feel::po::value< std::string >(), "filename of partitioned mesh")
        (prefixvm(prefix,"meshpartitioning.gmsh.partitions").c_str(), Feel::po::value< int >(), "number of partition")
        ;

    return envfsiOptions;
}

Feel::po::options_description modelbase_options(std::string const& prefix)
{
    Feel::po::options_description appliBaseOptions("Application Base options");
    appliBaseOptions.add_options()
        (prefixvm(prefix,"verbose").c_str(), Feel::po::value<bool>()->default_value( false ), "true or false to view verbose")
        (prefixvm(prefix,"verbose_allproc").c_str(), Feel::po::value<bool>()->default_value( false ), "true or false to view verbose for all proc")
        (prefixvm(prefix,"timers.activated").c_str(), Feel::po::value<bool>()->default_value( true ), "timers.activated")
        (prefixvm(prefix,"timers.save-master-rank").c_str(), Feel::po::value<bool>()->default_value( true ), "timers.save-master-rank")
        (prefixvm(prefix,"timers.save-max").c_str(), Feel::po::value<bool>()->default_value( false ), "timers.save-max")
        (prefixvm(prefix,"timers.save-min").c_str(), Feel::po::value<bool>()->default_value( false ), "timers.save-min")
        (prefixvm(prefix,"timers.save-mean").c_str(), Feel::po::value<bool>()->default_value( false ), "timers.save-mean")
        (prefixvm(prefix,"timers.save-all").c_str(), Feel::po::value<bool>()->default_value( false ), "timers.save-all")
        (prefixvm(prefix,"scalability-save").c_str(), Feel::po::value<bool>()->default_value( false ), "save-scalability")
        (prefixvm(prefix,"scalability-reinit-savefile").c_str(), Feel::po::value<bool>()->default_value( false ), "reinit-savefile")
        (prefixvm(prefix,"scalability-path").c_str(), Feel::po::value< std::string >(), "scalability-path")
        (prefixvm(prefix,"scalability-filename").c_str(), Feel::po::value< std::string >(), "scalability-filename")
        ;
    return appliBaseOptions;
}

Feel::po::options_description modelalgebraic_options(std::string const& prefix)
{
    Feel::po::options_description appliBaseOptions("Application Base Methods Num options");
    appliBaseOptions.add_options()
        (prefixvm(prefix,"verbose_solvertimer").c_str(), Feel::po::value<bool>()->default_value( false/*true*/ ), "true or false to view verbose")
        (prefixvm(prefix,"verbose_solvertimer_allproc").c_str(), Feel::po::value<bool>()->default_value( false ), "true or false to view verbose for all proc")
        (prefixvm(prefix,"linearsystem-cst-update").c_str(), Feel::po::value< bool >()->default_value( true ), "update matrix and rhs cst part")
        (prefixvm(prefix,"jacobian-linear-update").c_str(), Feel::po::value< bool >()->default_value( true ), "update linear part of the jacobian")
        (prefixvm(prefix,"residual-uselinearjac").c_str(), Feel::po::value< bool >()->default_value( true ), "update linear part of the residual with linear jacobian")
        (prefixvm(prefix,"preconditioner.contribution").c_str(), Feel::po::value< std::string >()->default_value("same_matrix"),
         "contribution in preconditioner : same_matrix, standart, extended ")
        (prefixvm(prefix,"use-cst-matrix").c_str(), Feel::po::value< bool >()->default_value( true ), "use-cst-matrix")
        (prefixvm(prefix,"use-cst-vector").c_str(), Feel::po::value< bool >()->default_value( true ), "use-cst-vector")
        (prefixvm(prefix,"error-if-solver-not-converged").c_str(), Feel::po::value< bool >()->default_value( false ), "error-if-solver-not-converged")
        (prefixvm(prefix,"clear-preconditioner-after-use").c_str(), Feel::po::value< bool >()->default_value( false ), "clear-preconditioner-after-use")
        (prefixvm(prefix,"graph-print-python").c_str(), Feel::po::value<bool>()->default_value( false ), "print graph in python script")
        (prefixvm(prefix,"graph-print-python-filename").c_str(), Feel::po::value< std::string >(), "filename python graph")
        ;
    return appliBaseOptions.add( modelbase_options(prefix ) );//.add( backend_options( prefix ) );
}


Feel::po::options_description modelnumerical_options(std::string const& prefix)
{
    Feel::po::options_description appliBaseOptions("Application Base options");
    appliBaseOptions.add_options()
        (prefixvm(prefix,"filename").c_str(), Feel::po::value<std::string>()->default_value( "" ), "json file describing model properties" )
        // mesh
        (prefixvm(prefix,"geofile").c_str(), Feel::po::value< std::string >(), "input geo file")
        (prefixvm(prefix,"mshfile").c_str(), Feel::po::value< std::string >(), "input msh file")
        // other
        (prefixvm(prefix,"rebuild_mesh_partitions").c_str(), Feel::po::value<bool>()->default_value( false ), "true or false to rebuild mesh partitions ")
        (prefixvm(prefix,"geomap").c_str(), Feel::po::value< std::string >()->default_value("opt"), "geomap strategy : ho, opt ")
        (prefixvm(prefix,"symbolic-expr.directory").c_str(), Feel::po::value< std::string >(), "symbolic-expr.directory");
        ;

    return appliBaseOptions
        .add( gmsh_options( prefix ) )
        .add( modelalgebraic_options( prefix ))
        .add( backend_options( prefix ) );
}

/**
 * generate options for the fluid solver
 */
Feel::po::options_description
densityviscosity_options(std::string const& prefix)
{
    Feel::po::options_description densityviscosityOptions("DensityViscosity options");
    densityviscosityOptions.add_options()
        (prefixvm(prefix,"rho").c_str(), Feel::po::value<double>()->default_value( 1050 ), "density [ kg.m^3]")
        (prefixvm(prefix,"mu").c_str(), Feel::po::value<double>()->default_value( 0.00345 ), "dynamic viscosity [ Pa.s = kg/(m.s^2) ]")
        (prefixvm(prefix,"viscosity.law").c_str(), Feel::po::value< std::string >()->default_value("newtonian"), "newtonian, power_law, walburn-schneck_law, carreau_law, carreau-yasuda_law ")
        (prefixvm(prefix,"viscosity.zero_shear").c_str(), Feel::po::value< double >()->default_value( 0.056 ), "parameter mu_0 for generalized Newtonian [ Pa.s ]  ")
        (prefixvm(prefix,"viscosity.infinite_shear").c_str(), Feel::po::value< double >()->default_value( 0.00345 ), "parameter mu_inf for generalized Newtonian [ Pa.s ] ")
        (prefixvm(prefix,"hematocrit").c_str(), Feel::po::value< double >()->default_value( 40 ), "hematocrit : RBC volume fraction (Vrbc/Vtotal) [ percentage ] ")
        (prefixvm(prefix,"power_law.n").c_str(), Feel::po::value< double >()->default_value( 0.6 ), "parameter n in power_law ")
        (prefixvm(prefix,"power_law.k").c_str(), Feel::po::value< double >()->default_value( 0.035 ), "parameter k in power_law [ Pa.s^n ] ")
        (prefixvm(prefix,"carreau_law.lambda").c_str(), Feel::po::value< double >()->default_value( 3.313 ), "parameter lambda in carreau_law [ s ] ")
        (prefixvm(prefix,"carreau_law.n").c_str(), Feel::po::value< double >()->default_value( 0.3568 ), "parameter n in carreau_law ")
        (prefixvm(prefix,"carreau-yasuda_law.lambda").c_str(), Feel::po::value< double >()->default_value( 1.902 ), "parameter lambda in carreau-yasuda_law [ s ] ")
        (prefixvm(prefix,"carreau-yasuda_law.n").c_str(), Feel::po::value< double >()->default_value( 0.22 ), "parameter n in carreau-yasuda_law ")
        (prefixvm(prefix,"carreau-yasuda_law.a").c_str(), Feel::po::value< double >()->default_value( 1.25 ), "parameter a in carreau-yasuda_law ")
        (prefixvm(prefix,"walburn-schneck_law.C1").c_str(), Feel::po::value< double >()->default_value( 0.00797 ), "parameter C1 in walburn-schneck_law ")
        (prefixvm(prefix,"walburn-schneck_law.C2").c_str(), Feel::po::value< double >()->default_value( 0.0608 ), "parameter C2 in walburn-schneck_law ")
        (prefixvm(prefix,"walburn-schneck_law.C3").c_str(), Feel::po::value< double >()->default_value( 0.00499 ), "parameter C3 in walburn-schneck_law ")
        (prefixvm(prefix,"walburn-schneck_law.C4").c_str(), Feel::po::value< double >()->default_value( 14.585 ), "parameter C4 in walburn-schneck_law [l/g] ")
        (prefixvm(prefix,"TPMA").c_str(), Feel::po::value< double >()->default_value( 25.9 ), "parameter TPMA (Total Proteins Minus Albumin) [ g/l ] ")
        ;
    
    return densityviscosityOptions;
}

Feel::po::options_description
fluidMechanics_options(std::string const& prefix)
{
    Feel::po::options_description fluidOptions("Fluid Mechanics options");
    fluidOptions.add_options()
        (prefixvm(prefix,"model").c_str(), Feel::po::value< std::string >(), "fluid model : Navier-Stokes,Stokes")
        (prefixvm(prefix,"solver").c_str(), Feel::po::value< std::string >(), "fluid solver")
        ( prefixvm(prefix,"start-by-solve-newtonian").c_str(), Feel::po::value<bool>()->default_value( false ), "start-by-solve-newtonian")
        ( prefixvm(prefix,"start-by-solve-stokes-stationary").c_str(), Feel::po::value<bool>()->default_value( false ), "start-by-solve-stokes-stationary")
        ( prefixvm(prefix,"start-by-solve-stokes-stationary.do-export").c_str(), Feel::po::value<bool>()->default_value( false ), "start-by-solve-stokes-stationary.do-export")
        ( prefixvm(prefix,"start-by-solve-stokes-stationary.time-value-used-in-bc").c_str(), Feel::po::value<double>()->default_value( 0. ), "time-value-used-in-bc")
        //(prefixvm(prefix,"strain_tensor.use-sym-tensor").c_str(), Feel::po::value< bool >()->default_value(true), "sym tensor or not ")

        (prefixvm(prefix,"stabilization-gls").c_str(), Feel::po::value<bool>()->default_value( false ), "apply stabilization method")
        (prefixvm(prefix,"stabilization-gls.type").c_str(), Feel::po::value<std::string>()->default_value( "gls" ), "supg,gls,gls-no-pspg, supg-pspg, pspg")
        (prefixvm(prefix,"stabilization-gls.parameter.method").c_str(), Feel::po::value<std::string>()->default_value( "eigenvalue" ), "method used for compute tau : eigenvalue, doubly-asymptotic-approximation")
        (prefixvm(prefix,"stabilization-gls.parameter.hsize.method").c_str(), Feel::po::value<std::string>()->default_value( "hmin" ), "hmin,h,meas")
        (prefixvm(prefix,"stabilization-gls.parameter.eigenvalue.penal-lambdaK").c_str(), Feel::po::value<double>()->default_value( 0. ), "apply stabilization method")
        (prefixvm(prefix,"stabilization-gls.convection-diffusion.location.expressions").c_str(), Feel::po::value<std::string>(), "expression which determinate the location where stab is applied")

        (prefixvm(prefix,"stabilisation-pspg").c_str(), Feel::po::value<bool>()->default_value( false ), "use stabilisation method")
        (prefixvm(prefix,"stabilisation-gls").c_str(), Feel::po::value<bool>()->default_value( false ), "use stabilisation method")
        (prefixvm(prefix,"stabilisation-cip-convection").c_str(), Feel::po::value<bool>()->default_value( false ), "use stabilisation method")
        (prefixvm(prefix,"stabilisation-cip-convection-gamma").c_str(), Feel::po::value<double>()->default_value( 1.0 ), "use stabilisation method")
        (prefixvm(prefix,"stabilisation-cip-pressure").c_str(), Feel::po::value<bool>()->default_value( false ), "use stabilisation method")
        (prefixvm(prefix,"stabilisation-cip-pressure-gamma").c_str(), Feel::po::value<double>()->default_value( 1.0 ), "use stabilisation method")
        (prefixvm(prefix,"stabilisation-cip-divergence").c_str(), Feel::po::value<bool>()->default_value( false ), "use stabilisation method")
        (prefixvm(prefix,"stabilisation-cip-divergence-gamma").c_str(), Feel::po::value<double>()->default_value( 1.0 ), "use stabilisation method")
        (prefixvm(prefix,"stabilisation-divergence").c_str(), Feel::po::value<bool>()->default_value( false ), "use stabilisation method")
        (prefixvm(prefix,"stabilisation-div-div").c_str(), Feel::po::value<bool>()->default_value( false ), "use stabilisation method")
        (prefixvm(prefix,"stabilisation-div-div-beta").c_str(), Feel::po::value< double >()->default_value( 1.0 ), "parameter beta in div-div stab ")
        (prefixvm(prefix,"marked-zones.markedfaces").c_str(), po::value<std::vector<std::string> >()->multitoken(), "marked-zone.markedfaces" )
        (prefixvm(prefix,"marked-zones.elements-from-markedfaces").c_str(), po::value<std::vector<std::string> >()->multitoken(), "marked-zone.elements-from-markedfaces" )
        (prefixvm(prefix,"marked-zones.expressions").c_str(), po::value<std::vector<std::string> >()->multitoken(), "marked-zone.expressions" )
        (prefixvm(prefix,"marked-zones.internal-faces").c_str(), po::value<bool>()->default_value(false), "marked-zone.internal-faces" )
        (prefixvm(prefix,"define-pressure-cst").c_str(), Feel::po::value<bool>()->default_value( false ), "maybe need to define the pressure constant if only dirichlet bc")
        (prefixvm(prefix,"define-pressure-cst.method").c_str(), Feel::po::value<std::string>()->default_value( "lagrange-multiplier"), " lagrange-multiplier or penalisation or algebraic")
        (prefixvm(prefix,"define-pressure-cst.penalisation-beta").c_str(), Feel::po::value< double >()->default_value( -10e-10 ), "parameter beta in cstpressure penalisation ")
        (prefixvm(prefix,"stabilisation-convection-energy").c_str(), Feel::po::value<bool>()->default_value( false ), "use stabilisation method")
        (prefixvm(prefix,"dirichletbc.type").c_str(), Feel::po::value<std::string>()->default_value( "elimination" ), "elimination, nitsche, lm")

        (prefixvm(prefix,"dirichletbc.lm.savemesh").c_str(), Feel::po::value<bool>()->default_value( false ), "export Lagrange multipliers mesh")
        (prefixvm(prefix,"dirichletbc.lm.use-submesh-relation").c_str(), Feel::po::value<bool>()->default_value( true ), "use submesh relation")
        (prefixvm(prefix,"dirichletbc.nitsche.gamma").c_str(), Feel::po::value<double>()->default_value( 10.0 ), "coeff for weak Dirichlet conditions")
        (prefixvm(prefix,"bc-slip-form").c_str(), Feel::po::value<int>()->default_value( 1 ), "formulation for slip condition (1 or 2)")
        (prefixvm(prefix,"bc-slip-gammaN").c_str(), Feel::po::value<double>()->default_value( 10.0 ), "coeff for weak Dirichlet conditions")
        (prefixvm(prefix,"bc-slip-gammaTau").c_str(), Feel::po::value<double>()->default_value( 10.0 ), "coeff for weak Dirichlet conditions")
        (prefixvm(prefix,"hovisu").c_str(), Feel::po::value<bool>(), "true or false for high order visualisation")
        (prefixvm(prefix,"hovisu.space-used").c_str(), Feel::po::value<std::string>()->default_value( "velocity" ), "velocity , pressure, p1 ")

        (prefixvm(prefix,"do_export_velocity").c_str(), Feel::po::value<bool>(), "doExportVelocity")
        (prefixvm(prefix,"do_export_pressure").c_str(), Feel::po::value<bool>(), "doExportPressure")
        (prefixvm(prefix,"do_export_displacement").c_str(), Feel::po::value<bool>(), "doExportDisplacement")
        (prefixvm(prefix,"do_export_vorticity").c_str(), Feel::po::value<bool>(), "doExportVorticity")
        (prefixvm(prefix,"do_export_normalstress").c_str(), Feel::po::value<bool>(), "doExportNormalStress")
        (prefixvm(prefix,"do_export_wallshearstress").c_str(), Feel::po::value<bool>(), "doExportWallShearStress")
        (prefixvm(prefix,"do_export_density").c_str(), Feel::po::value<bool>(), "doExportDensity")
        (prefixvm(prefix,"do_export_viscosity").c_str(), Feel::po::value<bool>(), "doExportViscosity")
        (prefixvm(prefix,"do_export_meshale").c_str(), Feel::po::value<bool>()->default_value( false ), "doExportMeshALE")
        (prefixvm(prefix,"do_export_all").c_str(), Feel::po::value<bool>(), "doExportAll")

        (prefixvm(prefix,"periodicity.translate-x").c_str(), Feel::po::value<double>()->default_value( 0.0 ), "periodicity.translate-x")
        (prefixvm(prefix,"periodicity.translate-y").c_str(), Feel::po::value<double>()->default_value( 0.0 ), "periodicity.translate-y")
        (prefixvm(prefix,"periodicity.translate-z").c_str(), Feel::po::value<double>()->default_value( 0.0 ), "periodicity.translate-z")
        (prefixvm(prefix,"periodicity.marker1").c_str(), Feel::po::value<std::string>(), "periodicity.marker1 ")
        (prefixvm(prefix,"periodicity.marker2").c_str(), Feel::po::value<std::string>(), "periodicity.marker2 ")
        (prefixvm(prefix,"periodicity.pressure-jump").c_str(), Feel::po::value<double>()->default_value(1.0), "periodicity.pressure-jump ")

        (prefixvm(prefix,"blockns.type").c_str(), Feel::po::value<std::string>()->default_value("PCD"), "type : PCD,PMM")
        (prefixvm(prefix,"preconditioner.attach-mass-matrix").c_str(), Feel::po::value<bool>()->default_value(false), "attach mass matrix")

        (prefixvm(prefix,"fluid-outlet.type").c_str(), Feel::po::value<std::string>()->default_value( "free" ), "type : free, windkessel ")
        (prefixvm(prefix,"fluid-outlet.windkessel.coupling").c_str(), Feel::po::value<std::string>()->default_value( "implicit" ), "explicit, implicit ")

        (prefixvm(prefix,"use-gravity-force").c_str(), Feel::po::value<bool>()->default_value(false), "use-gravity-force")
        (prefixvm(prefix,"gravity-force").c_str(), Feel::po::value<std::string>(), "gravity-force : (default is {0,-9.80665} or {0,0,-9.80665}")
        ;

    fluidOptions
        .add( modelnumerical_options( prefix ) )
        .add( bdf_options( prefix ) )
        .add( ts_options( prefix ) )
        .add( alemesh_options( prefix ) )
        .add( backend_options( prefixvm(prefix,"fluidinlet") ) )
        .add( densityviscosity_options( prefix ) )
        ;


    fluidOptions.add_options()
        (prefixvm(prefix,"use-thermodyn").c_str(), Feel::po::value<bool>()->default_value( false ), "coupling with energy equation")
        (prefixvm(prefix,"Boussinesq.ref-temperature").c_str(), Feel::po::value<double>()->default_value( 300. ), "Boussinesq ref-temperature T0");
    fluidOptions.add( thermoDynamics_options( prefixvm(prefix,"thermo") ) );

    return fluidOptions;
}

Feel::po::options_description
solidMechanics_options(std::string const& prefix)
{
    Feel::po::options_description solidOptions("Solid Mechanics options");
    solidOptions.add_options()
        (prefixvm(prefix,"rho").c_str(), Feel::po::value<double>()->default_value( 1.0 ), "density")
        (prefixvm(prefix,"youngmodulus").c_str(), Feel::po::value<double>()->default_value( 3.e6 ), "young modulus")
        (prefixvm(prefix,"coeffpoisson").c_str(), Feel::po::value<double>()->default_value( 0.3 ), "poisson coefficient")
        (prefixvm(prefix,"model").c_str(), Feel::po::value< std::string >()/*->default_value("Elasticity")*/, "struct model")
        (prefixvm(prefix,"material_law").c_str(), Feel::po::value< std::string >()->default_value("StVenantKirchhoff"), "StVenantKirchhoff, NeoHookean")
        (prefixvm(prefix,"mechanicalproperties.compressible.volumic-law").c_str(), Feel::po::value< std::string >()->default_value("classic"), "classic, simo1985")
        (prefixvm(prefix,"mechanicalproperties.compressible.neohookean.variant").c_str(),
         Feel::po::value< std::string >()->default_value("default"), "default, molecular-theory, molecular-theory-simo1985")
        (prefixvm(prefix,"formulation").c_str(), Feel::po::value<std::string>()->default_value( "displacement" ), "displacement,displacement-pressure")
        (prefixvm(prefix,"solver").c_str(), Feel::po::value< std::string >(), "struct solver")
        (prefixvm(prefix,"time-schema").c_str(), Feel::po::value< std::string >()->default_value("Newmark"), "time integration schema : Newmark, Generalized-Alpha")
        (prefixvm(prefix,"time-rho").c_str(), Feel::po::value< double >()->default_value(0.8), " Generalized-Alpha parameter")
        (prefixvm(prefix,"time-initial.displacement.files.directory").c_str(), Feel::po::value<std::string>(), "initial displacemen")
        (prefixvm(prefix,"time-initial.displacement.files.format").c_str(), Feel::po::value<std::string>()->default_value( "hdf5" ), "intial displacement file format")

        (prefixvm(prefix,"1dreduced-geofile").c_str(), Feel::po::value< std::string >(), "input geo file 1dreduced")
        (prefixvm(prefix,"1dreduced-thickness").c_str(), Feel::po::value< double >()->default_value(0.1), "1dreduced-thickness")
        (prefixvm(prefix,"1dreduced-radius").c_str(), Feel::po::value< double >()->default_value(0.5), "1dreduced-radius")

        (prefixvm(prefix,"hovisu").c_str(), Feel::po::value<bool>(), "true or false for high order visualisation")
        (prefixvm(prefix,"hovisu.space-used").c_str(), Feel::po::value<std::string>()->default_value( "displacement" ), "displacement, pressure, p1 ")
        (prefixvm(prefix,"do_export_displacement").c_str(), Feel::po::value<bool>(), "doExportDisplacement")
        (prefixvm(prefix,"do_export_velocity").c_str(), Feel::po::value<bool>(), "doExportVelocity")
        (prefixvm(prefix,"do_export_acceleration").c_str(), Feel::po::value<bool>(), "doExportAcceleration")
        (prefixvm(prefix,"do_export_normalstress").c_str(), Feel::po::value<bool>(), "doExportNormalStress")
        (prefixvm(prefix,"do_export_pressure").c_str(), Feel::po::value<bool>(), "doExportPressure")
        (prefixvm(prefix,"do_export_material_properties").c_str(), Feel::po::value<bool>(), "doExportMaterialsProp")
        (prefixvm(prefix,"do_export_velocityinterfacefromfluid").c_str(), Feel::po::value<bool>(), "doExportVelocityInterfaceFromFluid")
        (prefixvm(prefix,"do_export_all").c_str(), Feel::po::value<bool>(), "doExportAll")

        (prefixvm(prefix,"use-null-space").c_str(), Feel::po::value<bool>()->default_value( false ), "use-null-space")
        (prefixvm(prefix,"use-near-null-space").c_str(), Feel::po::value<bool>()->default_value( true ), "use-near-null-space")
        ;
    solidOptions.add( gmsh_options( prefixvm(prefix,"1dreduced") ) );
    return solidOptions.add( modelnumerical_options( prefix ) ).add( bdf_options( prefix ) ).add( ts_options( prefix ) ).add( on_options( prefix ) );
}

Feel::po::options_description
fluidStructInteraction_options( std::string const& prefix )
{
    Feel::po::options_description FSIoptions("FSI options");
    FSIoptions.add_options()
        (prefixvm(prefix,"hsize").c_str(), Feel::po::value<double>()->default_value( 0.1 ), "characteristic mesh size")
        (prefixvm(prefix,"fluid-mesh.markers").c_str(), po::value<std::vector<std::string> >()->multitoken(), "solid-mesh.markers" )
        (prefixvm(prefix,"solid-mesh.markers").c_str(), po::value<std::vector<std::string> >()->multitoken(), "solid-mesh.markers" )
        (prefixvm(prefix,"solid-mesh.extract-1d-from-fluid-mesh").c_str(), Feel::po::value<bool>()->default_value( false ), "solid-mesh.extract-1d-from-fluid-mesh")
        (prefixvm(prefix,"mesh-save.tag").c_str(),Feel::po::value< std::string >()->default_value(""), "mesh-tag")
        (prefixvm(prefix,"mesh-save.directory").c_str(),Feel::po::value< std::string >(), "mesh-directory")
        (prefixvm(prefix,"mesh-save.force-rebuild").c_str(), Feel::po::value<bool>()->default_value( false ), "mesh-save.force-rebuild")

        (prefixvm(prefix,"conforming-interface").c_str(), Feel::po::value<bool>()->default_value( false ), " fsi interface is conforme?")
        (prefixvm(prefix,"coupling-type").c_str(),Feel::po::value< std::string >()->default_value("Implicit"), " Implicit or Semi-Implicit")
        (prefixvm(prefix,"coupling-bc").c_str(),Feel::po::value< std::string >()->default_value("dirichlet-neumann"), " dirichlet-neumann, robin-robin,robin-neumann")

        (prefixvm(prefix,"fixpoint.tol").c_str(), Feel::po::value<double>()->default_value( 1.e-6 ), "tolerance pt fixe")
        (prefixvm(prefix,"fixpoint.initialtheta").c_str(), Feel::po::value<double>()->default_value( 1. ), "relax aitken parameter")
        (prefixvm(prefix,"fixpoint.min_theta").c_str(), Feel::po::value<double>()->default_value( 1.e-4 ), "min theta parameter")
        (prefixvm(prefix,"fixpoint.maxit").c_str(), Feel::po::value<int>()->default_value( 1000 ), "max iteration")
        (prefixvm(prefix,"fixpoint.minit-convergence").c_str(), Feel::po::value<int>()->default_value( 3 ), "max iteration")
        // additionals options if reuse-prec or reuse-jac are actived
        (prefixvm(prefix,"fluid.reuse-prec.rebuild-at-first-fsi-step").c_str(), Feel::po::value<bool>()->default_value( true ), " fsi fluid reuse-prec.rebuild-at-first-fsi-step")
        (prefixvm(prefix,"solid.reuse-prec.rebuild-at-first-fsi-step").c_str(), Feel::po::value<bool>()->default_value( true ), " fsi solid reuse-prec.rebuild-at-first-fsi-step")
        (prefixvm(prefix,"fluid.reuse-jac.rebuild-at-first-fsi-step").c_str(), Feel::po::value<bool>()->default_value( true ), " fsi fluid reuse-prec.rebuild-at-first-fsi-step")
        (prefixvm(prefix,"solid.reuse-jac.rebuild-at-first-fsi-step").c_str(), Feel::po::value<bool>()->default_value( true ), " fsi solid reuse-prec.rebuild-at-first-fsi-step")
        (prefixvm(prefix,"fluid.reuse-prec.activated-after-n-fsi-it").c_str(), Feel::po::value<int>()->default_value( 0 ), "activated-after-n-fsi-it")
        (prefixvm(prefix,"solid.reuse-prec.activated-after-n-fsi-it").c_str(), Feel::po::value<int>()->default_value( 0 ), "activated-after-n-fsi-it")
        (prefixvm(prefix,"fluid.reuse-prec.activated-only-if-greater-than-tol").c_str(), Feel::po::value<double>()->default_value( 1e8 ), "activated-only-if-greater-than-tol")
        (prefixvm(prefix,"solid.reuse-prec.activated-only-if-greater-than-tol").c_str(), Feel::po::value<double>()->default_value( 1e8 ), "activated-only-if-greater-than-tol")
        // coupling-nitsche-family : nitsche,robin-robin,robin-robin-genuine
        (prefixvm(prefix,"coupling-nitsche-family.gamma").c_str(), Feel::po::value<double>()->default_value( 2500 ), "nitsche parameters")
        (prefixvm(prefix,"coupling-nitsche-family.gamma0").c_str(), Feel::po::value<double>()->default_value( 1 ), "nitsche parameters")
        (prefixvm(prefix,"coupling-nitsche-family.alpha").c_str(), Feel::po::value<double>()->default_value( 1 ), "nitsche parameters")
        (prefixvm(prefix,"coupling-nitsche-family.use-aitken").c_str(), Feel::po::value<bool>()->default_value( false ), "use-aitken")
        // coupling-robin-neumann-generalized
        (prefixvm(prefix,"coupling-robin-neumann-generalized.use-interface-operator").c_str(), Feel::po::value<bool>()->default_value( true ),"use-interface-operator")
        (prefixvm(prefix,"coupling-robin-neumann-generalized.manual-scaling").c_str(), Feel::po::value<double>()->default_value( 1.0 ),"manual-scaling")
        (prefixvm(prefix,"coupling-robin-neumann-generalized.use-aitken").c_str(), Feel::po::value<bool>()->default_value( false ), "use-aitken")
        (prefixvm(prefix,"coupling-robin-neumann-generalized.without-interface-operator.precompute-mass-matrix").c_str(), Feel::po::value<bool>()->default_value( true ),"precompute-mass-matrix")


        (prefixvm(prefix,"transfert-velocity-F2S.use-extrapolation").c_str(), Feel::po::value<bool>()->default_value( true ), "transfert-velocity-F2S.use-extrapolation")
        ;
    return FSIoptions.add( modelnumerical_options(prefix) );
}


Feel::po::options_description
thermoDynamics_options(std::string const& prefix)
{
    Feel::po::options_description thermoDynamicsOptions("Thermo Dynamics options");
    thermoDynamicsOptions.add_options()
        (prefixvm(prefix,"thermal-conductivity").c_str(), Feel::po::value<double>()->default_value( 1 ), "thermal-conductivity [ W/(m*K) ]")
        (prefixvm(prefix,"rho").c_str(), Feel::po::value<double>()->default_value( 1 ), "density [ kg/(m^3) ]")
        (prefixvm(prefix,"heat-capacity").c_str(), Feel::po::value<double>()->default_value( 1 ), "heat-capacity [ J/(kg*K) ]")
        (prefixvm(prefix,"thermal-expansion").c_str(), Feel::po::value<double>()->default_value( 1e-4 ), "thermal-conductivity [ 1/K) ]")
        (prefixvm(prefix,"use_velocity-convection").c_str(), Feel::po::value<bool>()->default_value( false ), "use-velocity-convection")
        (prefixvm(prefix,"velocity-convection_is_incompressible").c_str(), Feel::po::value<bool>()->default_value( false ), "velocity-convection-is-incompressible")
        (prefixvm(prefix,"velocity-convection").c_str(), Feel::po::value<std::string>(), "math expression")
        (prefixvm(prefix,"initial-solution.temperature").c_str(), Feel::po::value<std::string>(), "math expression")
        (prefixvm(prefix,"do_export_all").c_str(), Feel::po::value<bool>()->default_value( false ), "do_export_all")
        (prefixvm(prefix,"do_export_velocity-convection").c_str(), Feel::po::value<bool>()->default_value( false ), "do_export_velocity-convection")

        (prefixvm(prefix,"stabilization-gls").c_str(), Feel::po::value<bool>()->default_value( false ), "apply stabilization method")
        (prefixvm(prefix,"stabilization-gls.type").c_str(), Feel::po::value<std::string>()->default_value( "gls" ), "supg,gls,unusual-gls")
        (prefixvm(prefix,"stabilization-gls.parameter.method").c_str(), Feel::po::value<std::string>()->default_value( "eigenvalue" ), "method used for compute tau : eigenvalue, doubly-asymptotic-approximation")
        (prefixvm(prefix,"stabilization-gls.parameter.hsize.method").c_str(), Feel::po::value<std::string>()->default_value( "hmin" ), "hmin,h,meas")
        (prefixvm(prefix,"stabilization-gls.parameter.eigenvalue.penal-lambdaK").c_str(), Feel::po::value<double>()->default_value( 0. ), "apply stabilization method")
        ;
    return thermoDynamicsOptions.add( modelnumerical_options( prefix ) ).add( bdf_options( prefix ) ).add( ts_options( prefix ) );
}
Feel::po::options_description
electricity_options(std::string const& prefix)
{
    Feel::po::options_description electricityOptions("Thermo Dynamics options");
    electricityOptions.add_options()
        (prefixvm(prefix,"electric-conductivity").c_str(), Feel::po::value<double>()->default_value( 1 ), "electric-conductivity")
        ;
    return electricityOptions.add( modelnumerical_options( prefix ) );
}
Feel::po::options_description
thermoElectric_options(std::string const& prefix)
{
    Feel::po::options_description thermoElectricOptions("Thermo Dynamics options");
    thermoElectricOptions.add_options()
        // (prefixvm(prefix,"electric.electric-conductivity").c_str(), Feel::po::value<double>()->default_value( 1 ), "electric-conductivity")
        (prefixvm(prefix,"do_export_all").c_str(), Feel::po::value<bool>()->default_value( false ), "do_export_all")
        ;
    thermoElectricOptions.add( thermoDynamics_options( prefixvm(prefix,"thermo") ) );
    thermoElectricOptions.add( electricity_options( prefixvm(prefix,"electric") ) );
    return thermoElectricOptions.add( modelnumerical_options( prefix ) );
}


Feel::po::options_description
advection_options(std::string const& prefix)
{
    Feel::po::options_description advectionOptions("Advection options");
    advectionOptions.add_options()
        (prefixvm(prefix,"model").c_str(), Feel::po::value< std::string >(), "advection model : Advection, Advection-Diffusion, Advection-Diffusion-Reaction")
        (prefixvm(prefix,"solver").c_str(), Feel::po::value< std::string >(), "advection solver")
        (prefixvm(prefix,"D").c_str(), Feel::po::value<double>()->default_value( 0 ), "diffusion coefficient [ m^2.s^-1 ]")
        (prefixvm(prefix,"R").c_str(), Feel::po::value<double>()->default_value( 0 ), "reaction coefficient [ s^-1 ]")
        (prefixvm(prefix,"advection-velocity").c_str(), Feel::po::value<std::string>(), "math expression")
        (prefixvm(prefix,"advec-stab-method").c_str(), Feel::po::value<std::string>()->default_value( "GALS" ), "stabilization method")
        (prefixvm(prefix,"advec-stab-coeff").c_str(), Feel::po::value<double>()->default_value( 1 ), "stabilization coefficient")
        (prefixvm(prefix,"export-all").c_str(), Feel::po::value<bool>()->default_value( false ), "do_export_all")
        (prefixvm(prefix,"export-advection-velocity").c_str(), Feel::po::value<bool>()->default_value( false ), "do_export_advection_velocity")
        (prefixvm(prefix,"export-diffusion").c_str(), Feel::po::value<bool>()->default_value( false ), "do_export_diffusion_coeff")
        (prefixvm(prefix,"export-reaction").c_str(), Feel::po::value<bool>()->default_value( false ), "do_export_reaction_coeff")
        (prefixvm(prefix,"export-source").c_str(), Feel::po::value<bool>()->default_value( false ), "do_export_source_field")
        ;
    return advectionOptions.add( modelnumerical_options( prefix ) ).add( bdf_options( prefix ) ).add( ts_options( prefix ) );
}

Feel::po::options_description
reinitializer_fm_options(std::string const& prefix)
{
    Feel::po::options_description reinitializerFMOptions("ReinitializerFM options");
    reinitializerFMOptions.add_options()
        (prefixvm(prefix,"use-marker2-as-done").c_str(), Feel::po::value<bool>()->default_value( false ), "use marker2 to mark initially done elements in fast-marching algorithm")
        ;

    return reinitializerFMOptions;
}

Feel::po::options_description
reinitializer_hj_options(std::string const& prefix)
{
    Feel::po::options_description reinitializerHJOptions("ReinitializerHJ options");
    reinitializerHJOptions.add_options()
        (prefixvm(prefix,"tol").c_str(), Feel::po::value<double>()->default_value( 0.03 ), "tolerance on residual to \"distance function\" of HJ reinitialized level set")
        (prefixvm(prefix,"max-iter").c_str(), Feel::po::value<int>()->default_value( 15 ), "maximum number of iterations for Hamilton-Jacobi reinitialization")
        (prefixvm(prefix,"thickness-heaviside").c_str(), Feel::po::value<double>(), "thickness of the interface (support for Heaviside used to compute sign function)")
        ;

    reinitializerHJOptions.add( advection_options( prefix ) );

    return reinitializerHJOptions;
}

Feel::po::options_description
levelset_options(std::string const& prefix)
{
    Feel::po::options_description levelsetOptions("Levelset options");
    levelsetOptions.add_options()
        //(prefixvm(prefix,"fm-use-markerdirac").c_str(), Feel::po::value<bool>()->default_value( false ), "use markerDirac to mark initially done elements in fast-marching")
        (prefixvm(prefix,"fm-smooth-coeff").c_str(), Feel::po::value<double>()->default_value(-1.), "smoothing coefficient for interface local projection, if <0 nodal projection is done instead")
        (prefixvm(prefix,"use-regularized-phi").c_str(), Feel::po::value<bool>()->default_value( false ), "use grad(phi)/|grad(phi)| to evaluate Dirac and Heaviside functions")
        (prefixvm(prefix,"h-d-nodal-proj").c_str(), Feel::po::value<bool>()->default_value( true ), "use nodal projection to compute dirac and heaviside functions (if false, use L2 projection)")
        (prefixvm(prefix,"thickness-interface").c_str(), Feel::po::value<double>(), "thickness of the interface (support for Dirac and Heaviside functions)")
        (prefixvm(prefix,"use-adaptive-thickness").c_str(), Feel::po::value<bool>()->default_value( false ), "automatically adapt the thickness of Dirac and Heaviside")
        (prefixvm(prefix,"reinit-method").c_str(), Feel::po::value<std::string>()->default_value( "fm" ), "levelset reinitialization method (fm: fast-marching, hj: hamilton-jacobi)")
        //(prefixvm(prefix,"use-smooth-reinit").c_str(), Feel::po::value<bool>()->default_value(false), "Use smooth reinitialization")
        (prefixvm(prefix,"fm-init-first-elts-strategy").c_str(), Feel::po::value<int>()->default_value(1), "strategy to initialize the first elements before the fast marching:\n0 = do nothing\n1 = interface local projection by nodal (phi) and smooth (|grad phi|) projections, smoothing coeff given by option fm-smooth-coeff \n2 = Hamilton Jacoby equation (with parameters given in options)")

        (prefixvm(prefix,"reinit-initial-value").c_str(), Feel::po::value<bool>()->default_value( false ), "reinitialize levelset after setting initial value")

        (prefixvm(prefix,"smooth-curvature").c_str(), Feel::po::value<bool>()->default_value( false ), "smooth curvature (use if the levelset has order < 2)")
        (prefixvm(prefix,"smoother.smooth-coeff").c_str(), Feel::po::value<double>()->default_value(0.1), "smoothing coefficient for curvature smoothing")
        (prefixvm(prefix,"smoother-vec.smooth-coeff").c_str(), Feel::po::value<double>()->default_value(0.1), "smoothing coefficient for curvature smoothing")

        (prefixvm(prefix,"use-gradient-augmented").c_str(), Feel::po::value<bool>()->default_value(false), "Advect modGradPhi independently")
        (prefixvm(prefix,"reinit-gradient-augmented").c_str(), Feel::po::value<bool>()->default_value(false), "Reinit modGradPhi when phi is reinitialized")

        (prefixvm(prefix,"use-stretch-augmented").c_str(), Feel::po::value<bool>()->default_value(false), "Advect stretch independently")
        (prefixvm(prefix,"reinit-stretch-augmented").c_str(), Feel::po::value<bool>()->default_value(false), "Reinit stretch when phi is reinitialized")

        (prefixvm(prefix,"do_export_gradphi").c_str(), Feel::po::value<bool>(), "doExportGradPhi")
        (prefixvm(prefix,"do_export_modgradphi").c_str(), Feel::po::value<bool>(), "doExportModGradPhi")
        (prefixvm(prefix,"do_export_modgradphi-advection").c_str(), Feel::po::value<bool>()->default_value(false), "doExportModGradPhi-Advection")
        (prefixvm(prefix,"do_export_stretch-advection").c_str(), Feel::po::value<bool>()->default_value(false), "doExportStretch-Advection")
        ;

    levelsetOptions
        .add( advection_options( prefix ) )
        .add( advection_options( prefixvm(prefix, "modgradphi-advection") ) )
        .add( advection_options( prefixvm(prefix, "stretch-advection") ) )
        .add( backend_options( prefixvm(prefix, "projector-l2") ) )
        .add( backend_options( prefixvm(prefix, "projector-l2-vec") ) )
        .add( backend_options( prefixvm(prefix, "smoother") ) )
        .add( backend_options( prefixvm(prefix, "smoother-vec") ) )
        .add( backend_options( prefixvm(prefix, "smoother-fm") ) )
        .add( reinitializer_fm_options( prefixvm(prefix, "reinit-fm") ) )
        .add( reinitializer_hj_options( prefixvm(prefix, "reinit-hj") ) )
        ;

    return levelsetOptions;
}

Feel::po::options_description
interfaceforces_options(std::string const& prefix)
{
    Feel::po::options_description interfaceForcesOptions("InterfaceForces options");
    interfaceForcesOptions.add_options()
        (prefixvm(prefix,"helfrich-bending-modulus").c_str(), Feel::po::value<double>()->default_value(0.), "Helfrich bending modulus k_B" )
        (prefixvm(prefix,"helfrich-force-impl").c_str(), Feel::po::value<int>()->default_value(0), "Implementation of Helfrich force" )

        (prefixvm(prefix,"inextensibility-force-coeff").c_str(), Feel::po::value<double>()->default_value(1), "Inextensibility force coefficient (Lambda)" )
        (prefixvm(prefix,"inextensibility-force-epsilon").c_str(), Feel::po::value<double>(), "Inextensibility force epsilon" )
        ;

    return interfaceForcesOptions;
}

Feel::po::options_description
multifluid_options(std::string const& prefix, uint16_type nls = 1)
{
    Feel::po::options_description multifluidOptions("MultiFluid options");
    multifluidOptions.add_options()
        (prefixvm(prefix,"nfluids").c_str(), Feel::po::value<int>()->default_value( 2 ), "total number of fluids (including surrounding one)")

        (prefixvm(prefix, "use-picard-iterations").c_str(), Feel::po::value<bool>()->default_value( false ), "solve NS-LS coupling with non-linear Picard iterations")

        (prefixvm(prefix, "enable-surface-tension").c_str(), Feel::po::value<bool>()->default_value( true ), "enable surface tension between fluids")
        (prefixvm(prefix,"surface-tension-coeff").c_str(), po::value<std::vector<double> >()->multitoken(), "surface tension coefficients" )
        ;

    multifluidOptions
        .add( modelnumerical_options( prefix ) )
        .add( fluidMechanics_options( prefixvm(prefix, "fluid") ) )
        .add( levelset_options( prefixvm(prefix, "levelset") ) )
        ;
    for( uint16_type n = 0; n < nls; ++n )
    {
        std::string levelset_prefix = prefixvm(prefix, (boost::format( "levelset%1%" ) %(n+1)).str());
        multifluidOptions.add( levelset_options( levelset_prefix ) );
        multifluidOptions.add( densityviscosity_options( levelset_prefix ) );
        multifluidOptions.add( interfaceforces_options( levelset_prefix ) );
        multifluidOptions.add_options()
            // Reinitialization
            (prefixvm(levelset_prefix,"reinit-every").c_str(), Feel::po::value<int>()->default_value( 10 ), "reinitialize levelset every n iterations" )
            (prefixvm(levelset_prefix,"reinit-smooth-every").c_str(), Feel::po::value<int>()->default_value( -1 ), "reinitialize levelset smoothly every n iterations (needs to be <= reinit-every)" )
            // Interface forces model
            (prefixvm(levelset_prefix,"interface-forces-model").c_str(), Feel::po::value<std::vector<std::string>>()->multitoken(), "models for interface forces (helfrich, ...)" )
            ;
    }

    return multifluidOptions;
}

Feel::po::options_description
alemesh_options(std::string const& prefix)
{
    po::options_description desc_options("alemesh options");
    desc_options.add_options()
        (prefixvm(prefix,"alemesh.type").c_str(), Feel::po::value<std::string>()->default_value( "harmonic" ), "type : harmonic, winslow")
        //(prefixvm(prefix,"alemesh.verbose").c_str(), Feel::po::value<bool>()->default_value( false ), "true or false to view verbose")
        //(prefixvm(prefix,"alemesh.verbose_allproc").c_str(), Feel::po::value<bool>()->default_value( false ), "true or false to view verbose for all proc")
        (prefixvm(prefix,"alemesh.verbose_solvertimer").c_str(), Feel::po::value<bool>()->default_value( true ), "true or false to view verbose")
        (prefixvm(prefix,"alemesh.verbose_solvertimer_allproc").c_str(), Feel::po::value<bool>()->default_value( false ), "true or false to view verbose for all proc")
        (prefixvm(prefix,"alemesh.winslow.solver").c_str(), Feel::po::value<std::string>()->default_value( "newton" ), "solver : linear, ptfixe, newton")
        (prefixvm(prefix,"alemesh.winslow.ptfixe.niter").c_str(), Feel::po::value<int>()->default_value( 10 ), "nb max iteration of point fixe")
        (prefixvm(prefix,"alemesh.winslow.ptfixe.tol").c_str(), Feel::po::value<double>()->default_value( 1e-5 ), "tol point fixe")
        (prefixvm(prefix,"alemesh.winslow.aitken.initialtheta").c_str(), Feel::po::value<double>()->default_value( 0.3 ), "initial theta of aitken relax")
        (prefixvm(prefix,"alemesh.harmonic.use_adaptive_penalisation").c_str(), Feel::po::value<bool>()->default_value( true ), "use tau penalisation in low formulation")
        (prefixvm(prefix,"alemesh.apply-ho-correction").c_str(), Feel::po::value<bool>()->default_value( true ), "do apply ho correction")
        //(prefixvm(prefix,"alemesh.export").c_str(), Feel::po::value<bool>()->default_value( false ), "true or false to export")
        ;
    return desc_options
        .add( bdf_options( prefixvm(prefix,"alemesh") ) )
        .add( ts_options( prefixvm(prefix,"alemesh") ) )
        .add( backend_options( prefixvm(prefix,"alemesh") ) )
        .add( modelbase_options( prefixvm(prefix,"alemesh") ) )
        .add( modelalgebraic_options( prefixvm(prefix,"alemesh.harmonic") ) )
        .add( modelalgebraic_options( prefixvm(prefix,"alemesh.winslow") ) )
        .add( backend_options( prefixvm(prefix,"alemesh.winslow.l2proj") ) )
        .add( backend_options( prefixvm(prefix,"alemesh.ho") ) );
}



Feel::po::options_description
feelmodels_options(std::string type)
{
    Feel::po::options_description FSIoptions("FSI options");

    FSIoptions.add( envfeelmodels_options("master") );

    if (type == "fluid")
        FSIoptions.add(fluidMechanics_options("fluid"));
    else if (type == "solid")
        FSIoptions.add(solidMechanics_options("solid"));
    else if ( type == "thermo-dynamics" )
        FSIoptions.add( thermoDynamics_options("thermo") );
    else if (type == "fsi")
        FSIoptions
            .add(fluidMechanics_options("fluid"))
            .add(solidMechanics_options("solid"))
            .add(fluidStructInteraction_options("fsi"));
    else if (type == "advection")
        FSIoptions.add(advection_options("advection"));
    else if (type == "levelset")
        FSIoptions.add(levelset_options("levelset"));
    else if (type == "multifluid")
        FSIoptions.add(multifluid_options("multifluid"));
    else if (type == "thermo-electric")
        FSIoptions.add(thermoElectric_options("thermo-electric"));
    else
        CHECK( false ) << "invalid type : " << type << " -> must be fluid,solid,thermo-dynamics,fsi";

    return FSIoptions
        .add( Feel::feel_options() );
}


} // namespace Feel