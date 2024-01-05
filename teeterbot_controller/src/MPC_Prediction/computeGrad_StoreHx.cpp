//
// File: computeGrad_StoreHx.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 05-Jan-2024 13:02:36
//

// Include Files
#include "computeGrad_StoreHx.h"
#include "MPC_Prediction_internal_types.h"
#include "rt_nonfinite.h"
#include "xgemv.h"
#include <algorithm>
#include <cstring>

// Function Definitions
//
// Arguments    : b_struct_T &obj
//                const double H[100]
//                const double f[10]
//                const double x[11]
// Return Type  : void
//
namespace coder {
namespace optim {
namespace coder {
namespace qpactiveset {
namespace Objective {
void computeGrad_StoreHx(b_struct_T &obj, const double H[100],
                         const double f[10], const double x[11])
{
  switch (obj.objtype) {
  case 5: {
    int ixlast;
    ixlast = obj.nvar;
    if (ixlast - 2 >= 0) {
      std::memset(&obj.grad[0], 0,
                  static_cast<unsigned int>(ixlast - 1) * sizeof(double));
    }
    obj.grad[obj.nvar - 1] = obj.gammaScalar;
  } break;
  case 3: {
    int ixlast;
    internal::blas::xgemv(obj.nvar, obj.nvar, H, obj.nvar, x, obj.Hx);
    ixlast = static_cast<unsigned char>(obj.nvar);
    if (ixlast - 1 >= 0) {
      std::copy(&obj.Hx[0], &obj.Hx[ixlast], &obj.grad[0]);
    }
    if (obj.hasLinear && (obj.nvar >= 1)) {
      ixlast = obj.nvar - 1;
      for (int idx{0}; idx <= ixlast; idx++) {
        obj.grad[idx] += f[idx];
      }
    }
  } break;
  default: {
    int ixlast;
    internal::blas::xgemv(obj.nvar, obj.nvar, H, obj.nvar, x, obj.Hx);
    ixlast = obj.nvar + 1;
    for (int idx{ixlast}; idx < 11; idx++) {
      obj.Hx[idx - 1] = 0.0 * x[idx - 1];
    }
    std::copy(&obj.Hx[0], &obj.Hx[10], &obj.grad[0]);
    if (obj.hasLinear && (obj.nvar >= 1)) {
      ixlast = obj.nvar - 1;
      for (int idx{0}; idx <= ixlast; idx++) {
        obj.grad[idx] += f[idx];
      }
    }
  } break;
  }
}

} // namespace Objective
} // namespace qpactiveset
} // namespace coder
} // namespace optim
} // namespace coder

//
// File trailer for computeGrad_StoreHx.cpp
//
// [EOF]
//
