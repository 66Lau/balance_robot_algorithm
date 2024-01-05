//
// File: linearForm_.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 05-Jan-2024 13:02:36
//

// Include Files
#include "linearForm_.h"
#include "rt_nonfinite.h"
#include <algorithm>
#include <cstring>

// Function Definitions
//
// Arguments    : boolean_T obj_hasLinear
//                int obj_nvar
//                double workspace[121]
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
void linearForm_(boolean_T obj_hasLinear, int obj_nvar, double workspace[121],
                 const double H[100], const double f[10], const double x[11])
{
  int beta1;
  beta1 = 0;
  if (obj_hasLinear) {
    beta1 = static_cast<unsigned char>(obj_nvar);
    if (beta1 - 1 >= 0) {
      std::copy(&f[0], &f[beta1], &workspace[0]);
    }
    beta1 = 1;
  }
  if (obj_nvar != 0) {
    int ix;
    if (beta1 != 1) {
      beta1 = static_cast<unsigned char>(obj_nvar);
      std::memset(&workspace[0], 0,
                  static_cast<unsigned int>(beta1) * sizeof(double));
    }
    ix = 0;
    beta1 = obj_nvar * (obj_nvar - 1) + 1;
    for (int iac{1}; obj_nvar < 0 ? iac >= beta1 : iac <= beta1;
         iac += obj_nvar) {
      double c;
      int i;
      c = 0.5 * x[ix];
      i = (iac + obj_nvar) - 1;
      for (int ia{iac}; ia <= i; ia++) {
        int i1;
        i1 = ia - iac;
        workspace[i1] += H[ia - 1] * c;
      }
      ix++;
    }
  }
}

} // namespace Objective
} // namespace qpactiveset
} // namespace coder
} // namespace optim
} // namespace coder

//
// File trailer for linearForm_.cpp
//
// [EOF]
//
