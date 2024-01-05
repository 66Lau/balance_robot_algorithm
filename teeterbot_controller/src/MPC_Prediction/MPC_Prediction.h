//
// File: MPC_Prediction.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 05-Jan-2024 13:02:36
//

#ifndef MPC_PREDICTION_H
#define MPC_PREDICTION_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
extern void MPC_Prediction(const double x_k[4], const double E[40],
                           const double H[100], double N, double p,
                           double u_k_data[], int u_k_size[1]);

#endif
//
// File trailer for MPC_Prediction.h
//
// [EOF]
//
