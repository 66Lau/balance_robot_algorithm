//
// File: compute_lambda.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 05-Jan-2024 13:02:36
//

// Include Files
#include "compute_lambda.h"
#include "MPC_Prediction_internal_types.h"
#include "MPC_Prediction_rtwutil.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <cstring>

// Function Definitions
//
// Arguments    : double workspace[121]
//                struct_T &solution
//                const b_struct_T &objective
//                const e_struct_T &qrmanager
// Return Type  : void
//
namespace coder {
namespace optim {
namespace coder {
namespace qpactiveset {
void compute_lambda(double workspace[121], struct_T &solution,
                    const b_struct_T &objective, const e_struct_T &qrmanager)
{
  int nActiveConstr_tmp;
  nActiveConstr_tmp = qrmanager.ncols;
  if (qrmanager.ncols > 0) {
    double c;
    int idx;
    int idxQR;
    boolean_T guard1{false};
    guard1 = false;
    if (objective.objtype != 4) {
      boolean_T nonDegenerate;
      c = 100.0 * static_cast<double>(qrmanager.mrows) * 2.2204460492503131E-16;
      if ((qrmanager.mrows > 0) && (qrmanager.ncols > 0)) {
        nonDegenerate = true;
      } else {
        nonDegenerate = false;
      }
      if (nonDegenerate) {
        boolean_T guard2{false};
        idx = nActiveConstr_tmp;
        guard2 = false;
        if (qrmanager.mrows < qrmanager.ncols) {
          idxQR = qrmanager.mrows + 11 * (qrmanager.ncols - 1);
          while ((idx > qrmanager.mrows) &&
                 (std::abs(qrmanager.QR[idxQR - 1]) >= c)) {
            idx--;
            idxQR -= 11;
          }
          nonDegenerate = (idx == qrmanager.mrows);
          if (nonDegenerate) {
            guard2 = true;
          }
        } else {
          guard2 = true;
        }
        if (guard2) {
          idxQR = idx + 11 * (idx - 1);
          while ((idx >= 1) && (std::abs(qrmanager.QR[idxQR - 1]) >= c)) {
            idx--;
            idxQR -= 12;
          }
          nonDegenerate = (idx == 0);
        }
      }
      if (!nonDegenerate) {
        solution.state = -7;
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }
    if (guard1) {
      if (qrmanager.mrows != 0) {
        std::memset(&workspace[0], 0,
                    static_cast<unsigned int>(nActiveConstr_tmp) *
                        sizeof(double));
        idx = 11 * (qrmanager.ncols - 1) + 1;
        for (int iac{1}; iac <= idx; iac += 11) {
          c = 0.0;
          idxQR = (iac + qrmanager.mrows) - 1;
          for (int ia{iac}; ia <= idxQR; ia++) {
            c += qrmanager.Q[ia - 1] * objective.grad[ia - iac];
          }
          idxQR = div_nde_s32_floor(iac - 1);
          workspace[idxQR] += c;
        }
      }
      for (int iac{nActiveConstr_tmp}; iac >= 1; iac--) {
        idx = (iac + (iac - 1) * 11) - 1;
        workspace[iac - 1] /= qrmanager.QR[idx];
        for (int ia{0}; ia <= iac - 2; ia++) {
          idxQR = (iac - ia) - 2;
          workspace[idxQR] -= workspace[iac - 1] * qrmanager.QR[(idx - ia) - 1];
        }
      }
      solution.lambda = -workspace[0];
    }
  }
}

} // namespace qpactiveset
} // namespace coder
} // namespace optim
} // namespace coder

//
// File trailer for compute_lambda.cpp
//
// [EOF]
//
