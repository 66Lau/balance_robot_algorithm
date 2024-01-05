//
// File: factorQR.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 05-Jan-2024 13:02:36
//

// Include Files
#include "factorQR.h"
#include "MPC_Prediction_internal_types.h"
#include "rt_nonfinite.h"
#include "xzgeqp3.h"
#include <algorithm>
#include <cstring>

// Function Definitions
//
// Arguments    : e_struct_T &obj
//                const double A[11]
//                int mrows
//                int ncols
// Return Type  : void
//
namespace coder {
namespace optim {
namespace coder {
namespace QRManager {
void factorQR(e_struct_T &obj, const double A[11], int mrows, int ncols)
{
  int i;
  boolean_T guard1{false};
  i = mrows * ncols;
  guard1 = false;
  if (i > 0) {
    for (int idx{0}; idx < ncols; idx++) {
      int ix0_tmp;
      ix0_tmp = 11 * idx;
      i = static_cast<unsigned char>(mrows);
      std::copy(&A[ix0_tmp], &A[ix0_tmp + i], &obj.QR[ix0_tmp]);
    }
    guard1 = true;
  } else if (i == 0) {
    obj.mrows = mrows;
    obj.ncols = ncols;
    obj.minRowCol = 0;
  } else {
    guard1 = true;
  }
  if (guard1) {
    obj.usedPivoting = false;
    obj.mrows = mrows;
    obj.ncols = ncols;
    for (int idx{0}; idx < ncols; idx++) {
      obj.jpvt[idx] = idx + 1;
    }
    if (mrows <= ncols) {
      i = mrows;
    } else {
      i = ncols;
    }
    obj.minRowCol = i;
    std::memset(&obj.tau[0], 0, 11U * sizeof(double));
    if (i >= 1) {
      internal::reflapack::qrf(obj.QR, mrows, ncols, i, obj.tau);
    }
  }
}

} // namespace QRManager
} // namespace coder
} // namespace optim
} // namespace coder

//
// File trailer for factorQR.cpp
//
// [EOF]
//
