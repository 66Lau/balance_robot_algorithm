//
// File: feasibleX0ForWorkingSet.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 05-Jan-2024 13:02:36
//

// Include Files
#include "feasibleX0ForWorkingSet.h"
#include "MPC_Prediction_internal_types.h"
#include "MPC_Prediction_rtwutil.h"
#include "computeQ_.h"
#include "factorQR.h"
#include "rt_nonfinite.h"
#include "xzgeqp3.h"
#include <algorithm>
#include <cmath>
#include <cstring>

// Function Definitions
//
// Arguments    : double workspace[121]
//                double xCurrent[11]
//                const f_struct_T &workingset
//                e_struct_T &qrmanager
// Return Type  : boolean_T
//
namespace coder {
namespace optim {
namespace coder {
namespace qpactiveset {
namespace initialize {
boolean_T feasibleX0ForWorkingSet(double workspace[121], double xCurrent[11],
                                  const f_struct_T &workingset,
                                  e_struct_T &qrmanager)
{
  double B[121];
  int mWConstr;
  int nVar;
  boolean_T nonDegenerateWset;
  mWConstr = workingset.nActiveConstr;
  nVar = workingset.nVar;
  nonDegenerateWset = true;
  if (mWConstr != 0) {
    double c;
    int br;
    int i;
    int i1;
    int iAcol;
    for (iAcol = 0; iAcol < mWConstr; iAcol++) {
      workspace[0] = 0.0;
      workspace[11] = 0.0;
    }
    if (mWConstr != 0) {
      i = 11 * (mWConstr - 1) + 1;
      for (iAcol = 1; iAcol <= i; iAcol += 11) {
        c = 0.0;
        i1 = (iAcol + nVar) - 1;
        for (br = iAcol; br <= i1; br++) {
          c += workingset.ATwset[br - 1] * xCurrent[br - iAcol];
        }
        i1 = div_nde_s32_floor(iAcol - 1);
        workspace[i1] -= c;
      }
    }
    if (mWConstr >= nVar) {
      int jBcol;
      i = static_cast<unsigned char>(nVar);
      qrmanager.usedPivoting = false;
      qrmanager.mrows = mWConstr;
      qrmanager.ncols = nVar;
      for (br = 0; br < i; br++) {
        iAcol = 11 * br;
        for (jBcol = 0; jBcol < mWConstr; jBcol++) {
          qrmanager.QR[jBcol + iAcol] = workingset.ATwset[br + 11 * jBcol];
        }
        qrmanager.jpvt[br] = br + 1;
      }
      if (mWConstr <= nVar) {
        i = mWConstr;
      } else {
        i = nVar;
      }
      qrmanager.minRowCol = i;
      std::copy(&qrmanager.QR[0], &qrmanager.QR[121], &B[0]);
      std::memset(&qrmanager.tau[0], 0, 11U * sizeof(double));
      if (i >= 1) {
        internal::reflapack::qrf(B, mWConstr, nVar, i, qrmanager.tau);
      }
      std::copy(&B[0], &B[121], &qrmanager.QR[0]);
      QRManager::computeQ_(qrmanager, mWConstr);
      std::copy(&workspace[0], &workspace[121], &B[0]);
      for (int b_i{0}; b_i <= 11; b_i += 11) {
        i = b_i + 1;
        i1 = b_i + nVar;
        if (i <= i1) {
          std::memset(&workspace[i + -1], 0,
                      static_cast<unsigned int>((i1 - i) + 1) * sizeof(double));
        }
      }
      br = -1;
      for (int b_i{0}; b_i <= 11; b_i += 11) {
        jBcol = -1;
        i = b_i + 1;
        i1 = b_i + nVar;
        for (int k{i}; k <= i1; k++) {
          c = 0.0;
          for (iAcol = 0; iAcol < mWConstr; iAcol++) {
            c += qrmanager.Q[(iAcol + jBcol) + 1] * B[(iAcol + br) + 1];
          }
          workspace[k - 1] += c;
          jBcol += 11;
        }
        br += 11;
      }
      for (int j{0}; j < 2; j++) {
        jBcol = 11 * j - 1;
        for (int k{nVar}; k >= 1; k--) {
          iAcol = 11 * (k - 1) - 1;
          i = k + jBcol;
          c = workspace[i];
          if (c != 0.0) {
            workspace[i] = c / qrmanager.QR[k + iAcol];
            i1 = static_cast<unsigned char>(k - 1);
            for (int b_i{0}; b_i < i1; b_i++) {
              int i2;
              i2 = (b_i + jBcol) + 1;
              workspace[i2] -= workspace[i] * qrmanager.QR[(b_i + iAcol) + 1];
            }
          }
        }
      }
    } else {
      int jBcol;
      QRManager::factorQR(qrmanager, workingset.ATwset, nVar, mWConstr);
      QRManager::computeQ_(qrmanager, qrmanager.minRowCol);
      for (int j{0}; j < 2; j++) {
        jBcol = 11 * j;
        for (int b_i{0}; b_i < mWConstr; b_i++) {
          iAcol = 11 * b_i;
          br = b_i + jBcol;
          c = workspace[br];
          i = static_cast<unsigned char>(b_i);
          for (int k{0}; k < i; k++) {
            c -= qrmanager.QR[k + iAcol] * workspace[k + jBcol];
          }
          workspace[br] = c / qrmanager.QR[b_i + iAcol];
        }
      }
      std::copy(&workspace[0], &workspace[121], &B[0]);
      for (int b_i{0}; b_i <= 11; b_i += 11) {
        i = b_i + 1;
        i1 = b_i + nVar;
        if (i <= i1) {
          std::memset(&workspace[i + -1], 0,
                      static_cast<unsigned int>((i1 - i) + 1) * sizeof(double));
        }
      }
      br = 0;
      for (int b_i{0}; b_i <= 11; b_i += 11) {
        jBcol = -1;
        i = br + 1;
        i1 = br + mWConstr;
        for (int j{i}; j <= i1; j++) {
          int i2;
          i2 = b_i + 1;
          iAcol = b_i + nVar;
          for (int k{i2}; k <= iAcol; k++) {
            workspace[k - 1] += B[j - 1] * qrmanager.Q[(jBcol + k) - b_i];
          }
          jBcol += 11;
        }
        br += 11;
      }
    }
    iAcol = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (iAcol <= static_cast<unsigned char>(nVar) - 1) {
        if (std::isinf(workspace[iAcol]) || std::isnan(workspace[iAcol])) {
          nonDegenerateWset = false;
          exitg1 = 1;
        } else {
          c = workspace[iAcol + 11];
          if (std::isinf(c) || std::isnan(c)) {
            nonDegenerateWset = false;
            exitg1 = 1;
          } else {
            iAcol++;
          }
        }
      } else {
        double constrViolation_basicX;
        iAcol = nVar - 1;
        for (int k{0}; k <= iAcol; k++) {
          workspace[k] += xCurrent[k];
        }
        c = 0.0;
        constrViolation_basicX = 0.0;
        if (workingset.sizes[3] > 0) {
          c = std::fmax(0.0, -workspace[workingset.indexLB[0] - 1]);
          constrViolation_basicX =
              std::fmax(0.0, -workspace[workingset.indexLB[0] + 10]);
        }
        if ((c <= 2.2204460492503131E-16) || (c < constrViolation_basicX)) {
          i = static_cast<unsigned char>(nVar);
          std::copy(&workspace[0], &workspace[i], &xCurrent[0]);
        } else {
          i = static_cast<unsigned char>(nVar);
          std::copy(&workspace[11], &workspace[11 + i], &xCurrent[0]);
        }
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  return nonDegenerateWset;
}

} // namespace initialize
} // namespace qpactiveset
} // namespace coder
} // namespace optim
} // namespace coder

//
// File trailer for feasibleX0ForWorkingSet.cpp
//
// [EOF]
//
