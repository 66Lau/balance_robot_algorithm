//
// File: setProblemType.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 05-Jan-2024 13:02:36
//

// Include Files
#include "setProblemType.h"
#include "MPC_Prediction_internal_types.h"
#include "rt_nonfinite.h"
#include <cstring>

// Function Definitions
//
// Arguments    : f_struct_T &obj
//                int PROBLEM_TYPE
// Return Type  : void
//
namespace coder {
namespace optim {
namespace coder {
namespace qpactiveset {
namespace WorkingSet {
void setProblemType(f_struct_T &obj, int PROBLEM_TYPE)
{
  switch (PROBLEM_TYPE) {
  case 3:
    obj.nVar = 10;
    obj.mConstr = 0;
    for (int i{0}; i < 5; i++) {
      obj.sizes[i] = obj.sizesNormal[i];
    }
    for (int i{0}; i < 6; i++) {
      obj.isActiveIdx[i] = obj.isActiveIdxNormal[i];
    }
    break;
  case 1: {
    int i;
    obj.nVar = 11;
    obj.mConstr = 1;
    for (i = 0; i < 5; i++) {
      obj.sizes[i] = obj.sizesPhaseOne[i];
    }
    for (i = 0; i < 6; i++) {
      obj.isActiveIdx[i] = obj.isActiveIdxPhaseOne[i];
    }
    obj.indexLB[0] = 11;
    obj.lb[10] = 0.0;
    i = obj.nActiveConstr;
    for (int colOffsetATw{1}; colOffsetATw <= i; colOffsetATw++) {
      obj.ATwset[10] = -1.0;
    }
    obj.isActiveConstr = false;
  } break;
  case 2: {
    int i;
    obj.nVar = 10;
    obj.mConstr = 0;
    for (i = 0; i < 5; i++) {
      obj.sizes[i] = obj.sizesRegularized[i];
    }
    if (obj.probType != 4) {
      i = obj.nActiveConstr;
      for (int idx_col{1}; idx_col <= i; idx_col++) {
        int colOffsetATw;
        colOffsetATw = 11 * (idx_col - 1);
        if (obj.Wid == 3) {
          int i1;
          i1 = obj.Wlocalidx + 9;
          for (int idx_row{11}; idx_row <= i1; idx_row++) {
            obj.ATwset[10] = 0.0;
          }
          obj.ATwset[(obj.Wlocalidx + colOffsetATw) + 9] = -1.0;
          i1 = obj.Wlocalidx + 11;
          if (i1 <= 10) {
            std::memset(&obj.ATwset[(i1 + colOffsetATw) + -1], 0,
                        static_cast<unsigned int>(
                            ((colOffsetATw - i1) - colOffsetATw) + 11) *
                            sizeof(double));
          }
        }
      }
    }
    for (i = 0; i < 6; i++) {
      obj.isActiveIdx[i] = obj.isActiveIdxRegularized[i];
    }
  } break;
  default: {
    int i;
    obj.nVar = 11;
    obj.mConstr = 1;
    for (i = 0; i < 5; i++) {
      obj.sizes[i] = obj.sizesRegPhaseOne[i];
    }
    for (i = 0; i < 6; i++) {
      obj.isActiveIdx[i] = obj.isActiveIdxRegPhaseOne[i];
    }
    obj.indexLB[0] = 11;
    obj.lb[10] = 0.0;
    i = obj.nActiveConstr;
    for (int colOffsetATw{1}; colOffsetATw <= i; colOffsetATw++) {
      obj.ATwset[10] = -1.0;
    }
    obj.isActiveConstr = false;
  } break;
  }
  obj.probType = PROBLEM_TYPE;
}

} // namespace WorkingSet
} // namespace qpactiveset
} // namespace coder
} // namespace optim
} // namespace coder

//
// File trailer for setProblemType.cpp
//
// [EOF]
//
