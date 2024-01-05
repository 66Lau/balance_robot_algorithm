//
// File: computeFval_ReuseHx.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 05-Jan-2024 13:02:36
//

// Include Files
#include "computeFval_ReuseHx.h"
#include "MPC_Prediction_internal_types.h"
#include "rt_nonfinite.h"
#include <algorithm>

// Function Definitions
//
// Arguments    : const b_struct_T &obj
//                double workspace[121]
//                const double f[10]
//                const double x[11]
// Return Type  : double
//
namespace coder {
namespace optim {
namespace coder {
namespace qpactiveset {
namespace Objective {
double computeFval_ReuseHx(const b_struct_T &obj, double workspace[121],
                           const double f[10], const double x[11])
{
  double val;
  switch (obj.objtype) {
  case 5:
    val = obj.gammaScalar * x[obj.nvar - 1];
    break;
  case 3: {
    if (obj.hasLinear) {
      int i;
      i = static_cast<unsigned char>(obj.nvar);
      for (int k{0}; k < i; k++) {
        workspace[k] = 0.5 * obj.Hx[k] + f[k];
      }
      val = 0.0;
      if (obj.nvar >= 1) {
        for (int k{0}; k < i; k++) {
          val += x[k] * workspace[k];
        }
      }
    } else {
      val = 0.0;
      if (obj.nvar >= 1) {
        int i;
        i = static_cast<unsigned char>(obj.nvar);
        for (int k{0}; k < i; k++) {
          val += x[k] * obj.Hx[k];
        }
      }
      val *= 0.5;
    }
  } break;
  default: {
    if (obj.hasLinear) {
      int i;
      i = static_cast<unsigned char>(obj.nvar);
      if (i - 1 >= 0) {
        std::copy(&f[0], &f[i], &workspace[0]);
      }
      i = 9 - obj.nvar;
      for (int k{0}; k <= i; k++) {
        workspace[obj.nvar + k] = 0.0;
      }
      val = 0.0;
      for (int k{0}; k < 10; k++) {
        double d;
        d = workspace[k] + 0.5 * obj.Hx[k];
        workspace[k] = d;
        val += x[k] * d;
      }
    } else {
      int i;
      val = 0.0;
      for (int k{0}; k < 10; k++) {
        val += x[k] * obj.Hx[k];
      }
      val *= 0.5;
      i = obj.nvar + 1;
      for (int k{i}; k < 11; k++) {
        val += x[k - 1] * 0.0;
      }
    }
  } break;
  }
  return val;
}

} // namespace Objective
} // namespace qpactiveset
} // namespace coder
} // namespace optim
} // namespace coder

//
// File trailer for computeFval_ReuseHx.cpp
//
// [EOF]
//
