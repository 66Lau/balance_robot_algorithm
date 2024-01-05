//
// File: computeFval.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 05-Jan-2024 13:02:36
//

// Include Files
#include "computeFval.h"
#include "MPC_Prediction_internal_types.h"
#include "linearForm_.h"
#include "rt_nonfinite.h"

// Function Definitions
//
// Arguments    : const b_struct_T &obj
//                double workspace[121]
//                const double H[100]
//                const double f[10]
//                const double x[11]
// Return Type  : double
//
namespace coder {
namespace optim {
namespace coder {
namespace qpactiveset {
namespace Objective {
double computeFval(const b_struct_T &obj, double workspace[121],
                   const double H[100], const double f[10], const double x[11])
{
  double val;
  switch (obj.objtype) {
  case 5:
    val = obj.gammaScalar * x[obj.nvar - 1];
    break;
  case 3: {
    linearForm_(obj.hasLinear, obj.nvar, workspace, H, f, x);
    val = 0.0;
    if (obj.nvar >= 1) {
      int i;
      i = static_cast<unsigned char>(obj.nvar);
      for (int idx{0}; idx < i; idx++) {
        val += x[idx] * workspace[idx];
      }
    }
  } break;
  default: {
    int i;
    linearForm_(obj.hasLinear, obj.nvar, workspace, H, f, x);
    i = obj.nvar + 1;
    for (int idx{i}; idx < 11; idx++) {
      workspace[idx - 1] = 0.0 * x[idx - 1];
    }
    val = 0.0;
    for (int idx{0}; idx < 10; idx++) {
      val += x[idx] * workspace[idx];
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
// File trailer for computeFval.cpp
//
// [EOF]
//
