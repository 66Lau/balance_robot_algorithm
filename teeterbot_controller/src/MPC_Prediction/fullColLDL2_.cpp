//
// File: fullColLDL2_.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 05-Jan-2024 13:02:36
//

// Include Files
#include "fullColLDL2_.h"
#include "MPC_Prediction_internal_types.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions
//
// Arguments    : c_struct_T &obj
//                int NColsRemain
//                double REG_PRIMAL
// Return Type  : void
//
namespace coder {
namespace optim {
namespace coder {
namespace DynamicRegCholManager {
void fullColLDL2_(c_struct_T &obj, int NColsRemain, double REG_PRIMAL)
{
  int jA;
  for (int k{0}; k < NColsRemain; k++) {
    double alpha1;
    double temp;
    int LD_diagOffset;
    int i;
    int offset1;
    int subMatrixDim;
    LD_diagOffset = 12 * k;
    temp = obj.FMat[LD_diagOffset];
    if (std::abs(temp) <= obj.regTol_) {
      temp += REG_PRIMAL;
      obj.FMat[LD_diagOffset] = temp;
    }
    alpha1 = -1.0 / temp;
    subMatrixDim = (NColsRemain - k) - 2;
    offset1 = LD_diagOffset + 2;
    for (jA = 0; jA <= subMatrixDim; jA++) {
      obj.workspace_[jA] = obj.FMat[(LD_diagOffset + jA) + 1];
    }
    if (!(alpha1 == 0.0)) {
      jA = LD_diagOffset;
      for (int j{0}; j <= subMatrixDim; j++) {
        temp = obj.workspace_[j];
        if (temp != 0.0) {
          int i1;
          temp *= alpha1;
          i = jA + 13;
          i1 = subMatrixDim + jA;
          for (int ijA{i}; ijA <= i1 + 13; ijA++) {
            obj.FMat[ijA - 1] += obj.workspace_[(ijA - jA) - 13] * temp;
          }
        }
        jA += 11;
      }
    }
    temp = 1.0 / obj.FMat[LD_diagOffset];
    i = LD_diagOffset + subMatrixDim;
    for (jA = offset1; jA <= i + 2; jA++) {
      obj.FMat[jA - 1] *= temp;
    }
  }
  jA = 12 * (NColsRemain - 1);
  if (std::abs(obj.FMat[jA]) <= obj.regTol_) {
    obj.FMat[jA] += REG_PRIMAL;
  }
}

} // namespace DynamicRegCholManager
} // namespace coder
} // namespace optim
} // namespace coder

//
// File trailer for fullColLDL2_.cpp
//
// [EOF]
//
