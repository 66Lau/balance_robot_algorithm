//
// File: compute_deltax.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 05-Jan-2024 13:02:36
//

// Include Files
#include "compute_deltax.h"
#include "MPC_Prediction_internal_types.h"
#include "MPC_Prediction_rtwutil.h"
#include "fullColLDL2_.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <cstring>

// Function Definitions
//
// Arguments    : const double H[100]
//                struct_T &solution
//                d_struct_T &memspace
//                const e_struct_T &qrmanager
//                c_struct_T &cholmanager
//                const b_struct_T &objective
// Return Type  : void
//
namespace coder {
namespace optim {
namespace coder {
namespace qpactiveset {
void compute_deltax(const double H[100], struct_T &solution,
                    d_struct_T &memspace, const e_struct_T &qrmanager,
                    c_struct_T &cholmanager, const b_struct_T &objective)
{
  int mNull_tmp;
  int nVar_tmp;
  nVar_tmp = qrmanager.mrows - 1;
  mNull_tmp = qrmanager.mrows - qrmanager.ncols;
  if (mNull_tmp <= 0) {
    if (nVar_tmp >= 0) {
      std::memset(&solution.searchDir[0], 0,
                  static_cast<unsigned int>(nVar_tmp + 1) * sizeof(double));
    }
  } else {
    int nVars;
    for (nVars = 0; nVars <= nVar_tmp; nVars++) {
      solution.searchDir[nVars] = -objective.grad[nVars];
    }
    if (qrmanager.ncols <= 0) {
      if (objective.objtype == 3) {
        double temp;
        int A_maxDiag_idx;
        int br;
        int lastColC;
        temp = 1.4901161193847656E-6 * static_cast<double>(qrmanager.mrows);
        cholmanager.ndims = qrmanager.mrows;
        for (nVars = 0; nVars <= nVar_tmp; nVars++) {
          A_maxDiag_idx = (nVar_tmp + 1) * nVars;
          lastColC = 11 * nVars;
          for (br = 0; br <= nVar_tmp; br++) {
            cholmanager.FMat[lastColC + br] = H[A_maxDiag_idx + br];
          }
        }
        if (qrmanager.mrows < 1) {
          A_maxDiag_idx = -1;
        } else {
          A_maxDiag_idx = 0;
          if (qrmanager.mrows > 1) {
            double smax;
            smax = std::abs(cholmanager.FMat[0]);
            for (br = 2; br <= nVar_tmp + 1; br++) {
              double s;
              s = std::abs(cholmanager.FMat[(br - 1) * 12]);
              if (s > smax) {
                A_maxDiag_idx = br - 1;
                smax = s;
              }
            }
          }
        }
        cholmanager.regTol_ = std::fmax(
            std::abs(cholmanager.FMat[A_maxDiag_idx + 11 * A_maxDiag_idx]) *
                2.2204460492503131E-16,
            std::abs(temp));
        DynamicRegCholManager::fullColLDL2_(cholmanager, qrmanager.mrows, temp);
        if (cholmanager.ConvexCheck) {
          nVars = 0;
          int exitg1;
          do {
            exitg1 = 0;
            if (nVars <= nVar_tmp) {
              if (cholmanager.FMat[nVars + 11 * nVars] <= 0.0) {
                cholmanager.info = -nVars - 1;
                exitg1 = 1;
              } else {
                nVars++;
              }
            } else {
              cholmanager.ConvexCheck = false;
              exitg1 = 1;
            }
          } while (exitg1 == 0);
        }
        if (cholmanager.info != 0) {
          solution.state = -6;
        } else {
          int i;
          br = cholmanager.ndims - 2;
          if (cholmanager.ndims != 0) {
            for (nVars = 0; nVars <= br + 1; nVars++) {
              A_maxDiag_idx = nVars + nVars * 11;
              i = br - nVars;
              for (int ar{0}; ar <= i; ar++) {
                lastColC = (nVars + ar) + 1;
                solution.searchDir[lastColC] -=
                    solution.searchDir[nVars] *
                    cholmanager.FMat[(A_maxDiag_idx + ar) + 1];
              }
            }
          }
          br = cholmanager.ndims;
          for (nVars = 0; nVars < br; nVars++) {
            solution.searchDir[nVars] /= cholmanager.FMat[nVars + 11 * nVars];
          }
          if (cholmanager.ndims != 0) {
            for (nVars = br; nVars >= 1; nVars--) {
              lastColC = (nVars - 1) * 11;
              temp = solution.searchDir[nVars - 1];
              i = nVars + 1;
              for (int ar{br}; ar >= i; ar--) {
                temp -= cholmanager.FMat[(lastColC + ar) - 1] *
                        solution.searchDir[ar - 1];
              }
              solution.searchDir[nVars - 1] = temp;
            }
          }
        }
      }
    } else {
      int nullStartIdx;
      int nullStartIdx_tmp;
      nullStartIdx_tmp = 11 * qrmanager.ncols;
      nullStartIdx = nullStartIdx_tmp + 1;
      if (objective.objtype == 5) {
        for (nVars = 0; nVars < mNull_tmp; nVars++) {
          memspace.workspace_double[nVars] =
              -qrmanager.Q[nVar_tmp + 11 * (qrmanager.ncols + nVars)];
        }
        if (qrmanager.mrows != 0) {
          int i;
          int lastColC;
          if (nVar_tmp >= 0) {
            std::memset(&solution.searchDir[0], 0,
                        static_cast<unsigned int>(nVar_tmp + 1) *
                            sizeof(double));
          }
          lastColC = 0;
          i = (nullStartIdx_tmp + 11 * (mNull_tmp - 1)) + 1;
          for (int A_maxDiag_idx{nullStartIdx}; A_maxDiag_idx <= i;
               A_maxDiag_idx += 11) {
            int i1;
            i1 = A_maxDiag_idx + nVar_tmp;
            for (nVars = A_maxDiag_idx; nVars <= i1; nVars++) {
              int i2;
              i2 = nVars - A_maxDiag_idx;
              solution.searchDir[i2] +=
                  qrmanager.Q[nVars - 1] * memspace.workspace_double[lastColC];
            }
            lastColC++;
          }
        }
      } else {
        double temp;
        int A_maxDiag_idx;
        int ar;
        int br;
        int i;
        int i1;
        int i2;
        int lastColC;
        if (objective.objtype == 3) {
          nVars = qrmanager.mrows;
          if (qrmanager.mrows != 0) {
            br = nullStartIdx_tmp;
            lastColC = 11 * (mNull_tmp - 1);
            for (int cr{0}; cr <= lastColC; cr += 11) {
              i = cr + 1;
              i1 = cr + nVars;
              if (i <= i1) {
                std::memset(&memspace.workspace_double[i + -1], 0,
                            static_cast<unsigned int>((i1 - i) + 1) *
                                sizeof(double));
              }
            }
            for (int cr{0}; cr <= lastColC; cr += 11) {
              ar = -1;
              i = br + 1;
              i1 = br + nVars;
              for (int ib{i}; ib <= i1; ib++) {
                i2 = cr + 1;
                A_maxDiag_idx = cr + nVars;
                for (int ic{i2}; ic <= A_maxDiag_idx; ic++) {
                  memspace.workspace_double[ic - 1] +=
                      qrmanager.Q[ib - 1] * H[(ar + ic) - cr];
                }
                ar += nVars;
              }
              br += 11;
            }
          }
          lastColC = 11 * (mNull_tmp - 1);
          for (int cr{0}; cr <= lastColC; cr += 11) {
            i = cr + 1;
            i1 = cr + mNull_tmp;
            if (i <= i1) {
              std::memset(&cholmanager.FMat[i + -1], 0,
                          static_cast<unsigned int>((i1 - i) + 1) *
                              sizeof(double));
            }
          }
          br = -1;
          for (int cr{0}; cr <= lastColC; cr += 11) {
            ar = nullStartIdx_tmp;
            i = cr + 1;
            i1 = cr + mNull_tmp;
            for (int ic{i}; ic <= i1; ic++) {
              temp = 0.0;
              for (A_maxDiag_idx = 0; A_maxDiag_idx < nVars; A_maxDiag_idx++) {
                temp += qrmanager.Q[A_maxDiag_idx + ar] *
                        memspace.workspace_double[(A_maxDiag_idx + br) + 1];
              }
              cholmanager.FMat[ic - 1] += temp;
              ar += 11;
            }
            br += 11;
          }
        }
        temp = 1.4901161193847656E-6 * static_cast<double>(mNull_tmp);
        cholmanager.ndims = mNull_tmp;
        A_maxDiag_idx = 0;
        if (mNull_tmp > 1) {
          double smax;
          smax = std::abs(cholmanager.FMat[0]);
          for (br = 2; br <= mNull_tmp; br++) {
            double s;
            s = std::abs(cholmanager.FMat[(br - 1) * 12]);
            if (s > smax) {
              A_maxDiag_idx = br - 1;
              smax = s;
            }
          }
        }
        cholmanager.regTol_ = std::fmax(
            std::abs(cholmanager.FMat[A_maxDiag_idx + 11 * A_maxDiag_idx]) *
                2.2204460492503131E-16,
            temp);
        DynamicRegCholManager::fullColLDL2_(cholmanager, mNull_tmp, temp);
        if (cholmanager.ConvexCheck) {
          nVars = 0;
          int exitg1;
          do {
            exitg1 = 0;
            if (nVars <= mNull_tmp - 1) {
              if (cholmanager.FMat[nVars + 11 * nVars] <= 0.0) {
                cholmanager.info = -nVars - 1;
                exitg1 = 1;
              } else {
                nVars++;
              }
            } else {
              cholmanager.ConvexCheck = false;
              exitg1 = 1;
            }
          } while (exitg1 == 0);
        }
        if (cholmanager.info != 0) {
          solution.state = -6;
        } else {
          if (qrmanager.mrows != 0) {
            std::memset(&memspace.workspace_double[0], 0,
                        static_cast<unsigned int>(mNull_tmp) * sizeof(double));
            i = (nullStartIdx_tmp + 11 * (mNull_tmp - 1)) + 1;
            for (A_maxDiag_idx = nullStartIdx; A_maxDiag_idx <= i;
                 A_maxDiag_idx += 11) {
              temp = 0.0;
              i1 = A_maxDiag_idx + nVar_tmp;
              for (nVars = A_maxDiag_idx; nVars <= i1; nVars++) {
                temp += qrmanager.Q[nVars - 1] *
                        objective.grad[nVars - A_maxDiag_idx];
              }
              i1 = div_nde_s32_floor((A_maxDiag_idx - nullStartIdx_tmp) - 1);
              memspace.workspace_double[i1] -= temp;
            }
          }
          br = cholmanager.ndims - 2;
          if (cholmanager.ndims != 0) {
            for (nVars = 0; nVars <= br + 1; nVars++) {
              A_maxDiag_idx = nVars + nVars * 11;
              i = br - nVars;
              for (ar = 0; ar <= i; ar++) {
                lastColC = (nVars + ar) + 1;
                memspace.workspace_double[lastColC] -=
                    memspace.workspace_double[nVars] *
                    cholmanager.FMat[(A_maxDiag_idx + ar) + 1];
              }
            }
          }
          br = cholmanager.ndims;
          for (nVars = 0; nVars < br; nVars++) {
            memspace.workspace_double[nVars] /=
                cholmanager.FMat[nVars + 11 * nVars];
          }
          if (cholmanager.ndims != 0) {
            for (nVars = br; nVars >= 1; nVars--) {
              lastColC = (nVars - 1) * 11;
              temp = memspace.workspace_double[nVars - 1];
              i = nVars + 1;
              for (ar = br; ar >= i; ar--) {
                temp -= cholmanager.FMat[(lastColC + ar) - 1] *
                        memspace.workspace_double[ar - 1];
              }
              memspace.workspace_double[nVars - 1] = temp;
            }
          }
          if (qrmanager.mrows != 0) {
            if (nVar_tmp >= 0) {
              std::memset(&solution.searchDir[0], 0,
                          static_cast<unsigned int>(nVar_tmp + 1) *
                              sizeof(double));
            }
            lastColC = 0;
            i = (nullStartIdx_tmp + 11 * (mNull_tmp - 1)) + 1;
            for (A_maxDiag_idx = nullStartIdx; A_maxDiag_idx <= i;
                 A_maxDiag_idx += 11) {
              i1 = A_maxDiag_idx + nVar_tmp;
              for (nVars = A_maxDiag_idx; nVars <= i1; nVars++) {
                i2 = nVars - A_maxDiag_idx;
                solution.searchDir[i2] += qrmanager.Q[nVars - 1] *
                                          memspace.workspace_double[lastColC];
              }
              lastColC++;
            }
          }
        }
      }
    }
  }
}

} // namespace qpactiveset
} // namespace coder
} // namespace optim
} // namespace coder

//
// File trailer for compute_deltax.cpp
//
// [EOF]
//
