//
// File: _coder_MPC_Prediction_api.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 05-Jan-2024 13:02:36
//

#ifndef _CODER_MPC_PREDICTION_API_H
#define _CODER_MPC_PREDICTION_API_H

// Include Files
#include "emlrt.h"
#include "tmwtypes.h"
#include <algorithm>
#include <cstring>

// Variable Declarations
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

// Function Declarations
void MPC_Prediction(real_T x_k[4], real_T E[40], real_T H[100], real_T N,
                    real_T p, real_T u_k_data[], int32_T u_k_size[1]);

void MPC_Prediction_api(const mxArray *const prhs[5], const mxArray **plhs);

void MPC_Prediction_atexit();

void MPC_Prediction_initialize();

void MPC_Prediction_terminate();

void MPC_Prediction_xil_shutdown();

void MPC_Prediction_xil_terminate();

#endif
//
// File trailer for _coder_MPC_Prediction_api.h
//
// [EOF]
//
