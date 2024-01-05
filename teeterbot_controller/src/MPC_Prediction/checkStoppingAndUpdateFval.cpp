//
// File: checkStoppingAndUpdateFval.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 05-Jan-2024 13:02:36
//

// Include Files
#include "checkStoppingAndUpdateFval.h"
#include "MPC_Prediction_internal_types.h"
#include "computeFval_ReuseHx.h"
#include "feasibleX0ForWorkingSet.h"
#include "rt_nonfinite.h"
#include <algorithm>
#include <cmath>

// Function Definitions
//
// Arguments    : int &activeSetChangeID
//                const double f[10]
//                struct_T &solution
//                d_struct_T &memspace
//                const b_struct_T &objective
//                const f_struct_T &workingset
//                e_struct_T &qrmanager
//                double options_ObjectiveLimit
//                boolean_T updateFval
// Return Type  : void
//
namespace coder {
namespace optim {
namespace coder {
namespace qpactiveset {
namespace stopping {
void checkStoppingAndUpdateFval(int &activeSetChangeID, const double f[10],
                                struct_T &solution, d_struct_T &memspace,
                                const b_struct_T &objective,
                                const f_struct_T &workingset,
                                e_struct_T &qrmanager,
                                double options_ObjectiveLimit,
                                boolean_T updateFval)
{
  solution.iterations++;
  if ((solution.iterations >= 100) &&
      ((solution.state != 1) || (objective.objtype == 5))) {
    solution.state = 0;
  }
  if (solution.iterations - solution.iterations / 50 * 50 == 0) {
    double tempMaxConstr;
    double x;
    x = 0.0;
    if (workingset.sizes[3] > 0) {
      x = std::fmax(0.0, -solution.xstar[workingset.indexLB[0] - 1]);
    }
    solution.maxConstr = x;
    tempMaxConstr = x;
    if (objective.objtype == 5) {
      tempMaxConstr = x - solution.xstar[objective.nvar - 1];
    }
    if (tempMaxConstr > 1.0E-8) {
      int i;
      boolean_T nonDegenerateWset;
      i = static_cast<unsigned char>(objective.nvar);
      if (i - 1 >= 0) {
        std::copy(&solution.xstar[0], &solution.xstar[i],
                  &solution.searchDir[0]);
      }
      nonDegenerateWset = initialize::feasibleX0ForWorkingSet(
          memspace.workspace_double, solution.searchDir, workingset, qrmanager);
      if ((!nonDegenerateWset) && (solution.state != 0)) {
        solution.state = -2;
      }
      activeSetChangeID = 0;
      tempMaxConstr = 0.0;
      if (workingset.sizes[3] > 0) {
        tempMaxConstr =
            std::fmax(0.0, -solution.searchDir[workingset.indexLB[0] - 1]);
      }
      if (tempMaxConstr < x) {
        if (i - 1 >= 0) {
          std::copy(&solution.searchDir[0], &solution.searchDir[i],
                    &solution.xstar[0]);
        }
        solution.maxConstr = tempMaxConstr;
      }
    }
  }
  if (updateFval && (options_ObjectiveLimit > rtMinusInf)) {
    solution.fstar = Objective::computeFval_ReuseHx(
        objective, memspace.workspace_double, f, solution.xstar);
    if ((solution.fstar < options_ObjectiveLimit) &&
        ((solution.state != 0) || (objective.objtype != 5))) {
      solution.state = 2;
    }
  }
}

} // namespace stopping
} // namespace qpactiveset
} // namespace coder
} // namespace optim
} // namespace coder

//
// File trailer for checkStoppingAndUpdateFval.cpp
//
// [EOF]
//
