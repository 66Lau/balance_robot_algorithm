//
// File: MPC_Prediction_rtwutil.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 05-Jan-2024 13:02:36
//

// Include Files
#include "MPC_Prediction_rtwutil.h"
#include "rt_nonfinite.h"

// Function Definitions
//
// Arguments    : int numerator
// Return Type  : int
//
int div_nde_s32_floor(int numerator)
{
  int i;
  if ((numerator < 0) && (numerator % 11 != 0)) {
    i = -1;
  } else {
    i = 0;
  }
  return numerator / 11 + i;
}

//
// File trailer for MPC_Prediction_rtwutil.cpp
//
// [EOF]
//
