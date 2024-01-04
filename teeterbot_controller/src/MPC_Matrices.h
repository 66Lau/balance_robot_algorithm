//
// File: MPC_Matrices.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 04-Jan-2024 19:50:21
//

#ifndef MPC_MATRICES_H
#define MPC_MATRICES_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
extern void MPC_Matrices(const double A[16], const double B[4],
                         const double Q[16], double R, const double F[16],
                         double N, coder::array<double, 2U> &E,
                         coder::array<double, 2U> &H);

#endif
//
// File trailer for MPC_Matrices.h
//
// [EOF]
//
