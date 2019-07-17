/*!
 * \file CInviscidVortexSolution.cpp
 * \brief Implementations of the member functions of CInviscidVortexSolution.
 * \author T. Economon, E. van der Weide
 * \version 6.2.0 "Falcon"
 *
 * The current SU2 release has been coordinated by the
 * SU2 International Developers Society <www.su2devsociety.org>
 * with selected contributions from the open-source community.
 *
 * The main research teams contributing to the current release are:
 *  - Prof. Juan J. Alonso's group at Stanford University.
 *  - Prof. Piero Colonna's group at Delft University of Technology.
 *  - Prof. Nicolas R. Gauger's group at Kaiserslautern University of Technology.
 *  - Prof. Alberto Guardone's group at Polytechnic University of Milan.
 *  - Prof. Rafael Palacios' group at Imperial College London.
 *  - Prof. Vincent Terrapon's group at the University of Liege.
 *  - Prof. Edwin van der Weide's group at the University of Twente.
 *  - Lab. of New Concepts in Aeronautics at Tech. Institute of Aeronautics.
 *
 * Copyright 2012-2019, Francisco D. Palacios, Thomas D. Economon,
 *                      Tim Albring, and the SU2 contributors.
 *
 * SU2 is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * SU2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with SU2. If not, see <http://www.gnu.org/licenses/>.
 */

#include "../../../include/toolboxes/MMS/CInviscidVortexSolution.hpp"

CInviscidVortexSolution::CInviscidVortexSolution(void) : CVerificationSolution() { }

CInviscidVortexSolution::CInviscidVortexSolution(unsigned short val_nDim,
                                                 unsigned short val_nVar,
                                                 unsigned short val_iMesh,
                                                 CConfig*       config)
  : CVerificationSolution(val_nDim, val_nVar, val_iMesh, config) {

  /*--- Write a message that the solution is initialized for the
   inviscid vortex test case. ---*/
  if ((rank == MASTER_NODE) && (val_iMesh == MESH_0)) {
    cout << endl;
    cout << "Warning: Fluid properties and solution are being " << endl;
    cout << "         initialized for the inviscid vortex case!!!" << endl;
    cout << endl << flush;
  }

  /*--- Store the inviscid vortex specific parameters here. ---*/
  x0Vortex    = -0.5;     // Initial x-coordinate of the vortex center.
  y0Vortex    =  0.0;     // Initial y-coordinate of the vortex center.
  RVortex     =  0.1;     // Radius of the vortex.
  epsVortex   =  1.0;     // Strength of the vortex.

  /* Get the Mach number and advection angle (in degrees). */
  MachVortex  = config->GetMach();
  thetaVortex = config->GetAoA();

  /*--- Useful coefficients in which Gamma is present. ---*/
  Gamma    = config->GetGamma();
  Gm1      = Gamma - 1.0;
  ovGm1    = 1.0/Gm1;
  gamOvGm1 = ovGm1*Gamma;

  /*--- Perform some sanity and error checks for this solution here. ---*/
  if((config->GetUnsteady_Simulation() != TIME_STEPPING) &&
     (config->GetUnsteady_Simulation() != DT_STEPPING_1ST) &&
     (config->GetUnsteady_Simulation() != DT_STEPPING_2ND))
    SU2_MPI::Error("Unsteady mode must be selected for the inviscid vortex",
                   CURRENT_FUNCTION);

  if(config->GetKind_Regime() != COMPRESSIBLE)
    SU2_MPI::Error("Compressible flow equations must be selected for the inviscid vortex",
                   CURRENT_FUNCTION);

  if((config->GetKind_Solver() != EULER) &&
     (config->GetKind_Solver() != FEM_EULER))
    SU2_MPI::Error("Euler equations must be selected for the inviscid vortex",
                   CURRENT_FUNCTION);

  if((config->GetKind_FluidModel() != STANDARD_AIR) &&
     (config->GetKind_FluidModel() != IDEAL_GAS))
    SU2_MPI::Error("Standard air or ideal gas must be selected for the inviscid vortex",
                   CURRENT_FUNCTION);

  if(fabs(config->GetPressure_FreeStreamND() - 1.0) > 1.e-8)
    SU2_MPI::Error("Free-stream pressure must be 1.0 for the inviscid vortex",
                   CURRENT_FUNCTION);

  if(fabs(config->GetDensity_FreeStreamND() - 1.0) > 1.e-8)
    SU2_MPI::Error("Free-stream density must be 1.0 for the inviscid vortex",
                   CURRENT_FUNCTION);
}

CInviscidVortexSolution::~CInviscidVortexSolution(void) { }

void CInviscidVortexSolution::GetBCState(const su2double *val_coords,
                                         const su2double val_t,
                                         su2double       *val_solution) {

  /*--- For the case that the inviscid vortex is run with boundary
        conditions (other possibility is with periodic conditions),
        the exact solution is prescribed on the boundaries. ---*/
  GetSolution(val_coords, val_t, val_solution);
}

void CInviscidVortexSolution::GetSolution(const su2double *val_coords,
                                          const su2double val_t,
                                          su2double       *val_solution) {

  /* Compute the free stream velocities in x- and y-direction. */
  const su2double VelInf = MachVortex*sqrt(Gamma);
  const su2double uInf   = VelInf*cos(thetaVortex*PI_NUMBER/180.0);
  const su2double vInf   = VelInf*sin(thetaVortex*PI_NUMBER/180.0);

  /* Compute the coordinates relative to the center of the vortex. */
  const su2double dx = val_coords[0] - (x0Vortex + val_t*uInf);
  const su2double dy = val_coords[1] - (y0Vortex + val_t*vInf);

  /* Compute the components of the velocity. */
  su2double f  = 1.0 - (dx*dx + dy*dy)/(RVortex*RVortex);
  su2double t1 = epsVortex*dy*exp(0.5*f)/(2.0*PI_NUMBER*RVortex);
  su2double u  = uInf - VelInf*t1;

  t1          = epsVortex*dx*exp(0.5*f)/(2.0*PI_NUMBER*RVortex);
  su2double v = vInf + VelInf*t1;

  /* Compute the density and the pressure. */
  t1 = 1.0 - epsVortex*epsVortex*Gm1
     *       MachVortex*MachVortex*exp(f)/(8.0*PI_NUMBER*PI_NUMBER);

  su2double rho = pow(t1,ovGm1);
  su2double p   = pow(t1,gamOvGm1);

  /* Compute the conservative variables. Note that both 2D and 3D
     cases are treated correctly. */
  val_solution[0]      = rho;
  val_solution[1]      = rho*u;
  val_solution[2]      = rho*v;
  val_solution[3]      = 0.0;
  val_solution[nVar-1] = p*ovGm1 + 0.5*rho*(u*u + v*v);
}
