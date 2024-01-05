//
// File: addBoundToActiveSetMatrix_.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 05-Jan-2024 13:02:36
//

// Include Files
#include "addBoundToActiveSetMatrix_.h"
#include "MPC_Prediction_internal_types.h"
#include "rt_nonfinite.h"
#include <cstring>

// Function Definitions
//
// Arguments    : f_struct_T &obj
//                int TYPE
//                int idx_local
// Return Type  : void
//
namespace coder {
namespace optim {
namespace coder {
namespace qpactiveset {
namespace WorkingSet {
void addBoundToActiveSetMatrix_(f_struct_T &obj, int TYPE, int idx_local)
{
  int colOffset;
  int i;
  int idx_bnd_local;
  obj.nWConstr[TYPE - 1]++;
  obj.isActiveConstr = true;
  obj.nActiveConstr++;
  obj.Wid = TYPE;
  obj.Wlocalidx = idx_local;
  colOffset = 11 * (obj.nActiveConstr - 1) - 1;
  if (TYPE != 5) {
    idx_bnd_local = obj.indexLB[0];
    obj.bwset = 0.0;
  } else {
    // A check that is always false is detected at compile-time. Eliminating
    // code that follows.
  }
  if (idx_bnd_local - 2 >= 0) {
    std::memset(&obj.ATwset[colOffset + 1], 0,
                static_cast<unsigned int>(
                    ((idx_bnd_local + colOffset) - colOffset) - 1) *
                    sizeof(double));
  }
  obj.ATwset[idx_bnd_local + colOffset] =
      2.0 * static_cast<double>(TYPE == 5) - 1.0;
  idx_bnd_local++;
  i = obj.nVar;
  if (idx_bnd_local <= i) {
    std::memset(&obj.ATwset[idx_bnd_local + colOffset], 0,
                static_cast<unsigned int>(
                    (((i + colOffset) - idx_bnd_local) - colOffset) + 1) *
                    sizeof(double));
  }
  switch (obj.probType) {
  case 3:
  case 2:
    break;
  default:
    obj.ATwset[obj.nVar + colOffset] = -1.0;
    break;
  }
}

} // namespace WorkingSet
} // namespace qpactiveset
} // namespace coder
} // namespace optim
} // namespace coder

//
// File trailer for addBoundToActiveSetMatrix_.cpp
//
// [EOF]
//
