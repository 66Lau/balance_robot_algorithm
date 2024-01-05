//
// File: computeFirstOrderOpt.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 05-Jan-2024 13:02:36
//

// Include Files
#include "computeFirstOrderOpt.h"
#include "MPC_Prediction_internal_types.h"
#include "rt_nonfinite.h"
#include <algorithm>
#include <cmath>

// Function Definitions
//
// Arguments    : struct_T &solution
//                const b_struct_T &objective
//                int workingset_nVar
//                const double workingset_ATwset[11]
//                int workingset_nActiveConstr
//                double workspace[121]
// Return Type  : void
//
namespace coder {
namespace optim {
namespace coder {
namespace qpactiveset {
namespace parseoutput {
void computeFirstOrderOpt(struct_T &solution, const b_struct_T &objective,
                          int workingset_nVar,
                          const double workingset_ATwset[11],
                          int workingset_nActiveConstr, double workspace[121])
{
  double smax;
  int idxmax;
  int k;
  idxmax = static_cast<unsigned char>(workingset_nVar);
  std::copy(&objective.grad[0], &objective.grad[idxmax], &workspace[0]);
  if (workingset_nActiveConstr != 0) {
    idxmax = 11 * (workingset_nActiveConstr - 1) + 1;
    for (int iac{1}; iac <= idxmax; iac += 11) {
      k = (iac + workingset_nVar) - 1;
      for (int ia{iac}; ia <= k; ia++) {
        int i;
        i = ia - iac;
        workspace[i] += workingset_ATwset[ia - 1] * solution.lambda;
      }
    }
  }
  idxmax = 1;
  smax = std::abs(workspace[0]);
  for (k = 2; k <= workingset_nVar; k++) {
    double s;
    s = std::abs(workspace[k - 1]);
    if (s > smax) {
      idxmax = k;
      smax = s;
    }
  }
  solution.firstorderopt = std::abs(workspace[idxmax - 1]);
}

} // namespace parseoutput
} // namespace qpactiveset
} // namespace coder
} // namespace optim
} // namespace coder

//
// File trailer for computeFirstOrderOpt.cpp
//
// [EOF]
//
