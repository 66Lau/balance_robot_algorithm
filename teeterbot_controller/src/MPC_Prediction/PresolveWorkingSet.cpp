//
// File: PresolveWorkingSet.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 05-Jan-2024 13:02:36
//

// Include Files
#include "PresolveWorkingSet.h"
#include "MPC_Prediction_internal_types.h"
#include "RemoveDependentIneq_.h"
#include "computeQ_.h"
#include "countsort.h"
#include "factorQRE.h"
#include "feasibleX0ForWorkingSet.h"
#include "rt_nonfinite.h"
#include <algorithm>
#include <cmath>
#include <cstring>

// Function Definitions
//
// Arguments    : struct_T &solution
//                d_struct_T &memspace
//                f_struct_T &workingset
//                e_struct_T &qrmanager
// Return Type  : void
//
namespace coder {
namespace optim {
namespace coder {
namespace qpactiveset {
namespace initialize {
void PresolveWorkingSet(struct_T &solution, d_struct_T &memspace,
                        f_struct_T &workingset, e_struct_T &qrmanager)
{
  double tol;
  int idxDiag;
  int mTotalWorkingEq_tmp_tmp;
  int mWorkingFixed;
  int nDepInd;
  int totalRank;
  solution.state = 82;
  mWorkingFixed = workingset.nWConstr[0];
  mTotalWorkingEq_tmp_tmp = workingset.nWConstr[0] + workingset.nWConstr[1];
  nDepInd = 0;
  if (mTotalWorkingEq_tmp_tmp > 0) {
    int i;
    i = static_cast<unsigned char>(workingset.nVar);
    for (totalRank = 0; totalRank < mTotalWorkingEq_tmp_tmp; totalRank++) {
      for (idxDiag = 0; idxDiag < i; idxDiag++) {
        qrmanager.QR[totalRank + 11 * idxDiag] =
            workingset.ATwset[idxDiag + 11 * totalRank];
      }
    }
    nDepInd = mTotalWorkingEq_tmp_tmp - workingset.nVar;
    if (nDepInd <= 0) {
      nDepInd = 0;
    }
    std::memset(&qrmanager.jpvt[0], 0,
                static_cast<unsigned int>(i) * sizeof(int));
    QRManager::factorQRE(qrmanager, mTotalWorkingEq_tmp_tmp, workingset.nVar);
    tol = 100.0 * static_cast<double>(workingset.nVar) * 2.2204460492503131E-16;
    totalRank = workingset.nVar;
    if (totalRank > mTotalWorkingEq_tmp_tmp) {
      totalRank = mTotalWorkingEq_tmp_tmp;
    }
    idxDiag = totalRank + 11 * (totalRank - 1);
    while ((idxDiag > 0) && (std::abs(qrmanager.QR[idxDiag - 1]) < tol)) {
      idxDiag -= 12;
      nDepInd++;
    }
    if (nDepInd > 0) {
      boolean_T exitg1;
      QRManager::computeQ_(qrmanager, qrmanager.mrows);
      idxDiag = 0;
      exitg1 = false;
      while ((!exitg1) && (idxDiag <= nDepInd - 1)) {
        double qtb;
        totalRank = 11 * ((mTotalWorkingEq_tmp_tmp - idxDiag) - 1);
        qtb = 0.0;
        for (int k{0}; k < mTotalWorkingEq_tmp_tmp; k++) {
          qtb += qrmanager.Q[totalRank + k] * 0.0;
        }
        if (qtb >= tol) {
          nDepInd = -1;
          exitg1 = true;
        } else {
          idxDiag++;
        }
      }
    }
    if (nDepInd > 0) {
      for (idxDiag = 0; idxDiag < mTotalWorkingEq_tmp_tmp; idxDiag++) {
        totalRank = 11 * idxDiag;
        std::copy(&workingset.ATwset[totalRank],
                  &workingset.ATwset[totalRank + i], &qrmanager.QR[totalRank]);
      }
      for (idxDiag = 0; idxDiag < mWorkingFixed; idxDiag++) {
        qrmanager.jpvt[idxDiag] = 1;
      }
      i = workingset.nWConstr[0] + 1;
      if (i <= mTotalWorkingEq_tmp_tmp) {
        std::memset(
            &qrmanager.jpvt[i + -1], 0,
            static_cast<unsigned int>((mTotalWorkingEq_tmp_tmp - i) + 1) *
                sizeof(int));
      }
      QRManager::factorQRE(qrmanager, workingset.nVar, mTotalWorkingEq_tmp_tmp);
      for (idxDiag = 0; idxDiag < nDepInd; idxDiag++) {
        memspace.workspace_int[idxDiag] =
            qrmanager.jpvt[(mTotalWorkingEq_tmp_tmp - nDepInd) + idxDiag];
      }
      utils::countsort(memspace.workspace_int, nDepInd, memspace.workspace_sort,
                       1, mTotalWorkingEq_tmp_tmp);
      for (idxDiag = nDepInd; idxDiag >= 1; idxDiag--) {
        i = memspace.workspace_int[idxDiag - 1];
        if (i <= mTotalWorkingEq_tmp_tmp) {
          if ((workingset.nActiveConstr == mTotalWorkingEq_tmp_tmp) ||
              (i == mTotalWorkingEq_tmp_tmp)) {
            workingset.mEqRemoved++;
            // A check that is always false is detected at compile-time.
            // Eliminating code that follows.
          } else {
            workingset.mEqRemoved++;
            // A check that is always false is detected at compile-time.
            // Eliminating code that follows.
          }
        }
      }
    }
  }
  if ((nDepInd != -1) && (workingset.nActiveConstr <= 11)) {
    boolean_T guard1{false};
    boolean_T okWorkingSet;
    RemoveDependentIneq_(workingset, qrmanager, memspace, 100.0);
    okWorkingSet = feasibleX0ForWorkingSet(
        memspace.workspace_double, solution.xstar, workingset, qrmanager);
    guard1 = false;
    if (!okWorkingSet) {
      RemoveDependentIneq_(workingset, qrmanager, memspace, 1000.0);
      okWorkingSet = feasibleX0ForWorkingSet(
          memspace.workspace_double, solution.xstar, workingset, qrmanager);
      if (!okWorkingSet) {
        solution.state = -7;
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }
    if (guard1 &&
        (workingset.nWConstr[0] + workingset.nWConstr[1] == workingset.nVar)) {
      tol = 0.0;
      if (workingset.sizes[3] > 0) {
        tol = std::fmax(0.0, -solution.xstar[workingset.indexLB[0] - 1]);
      }
      if (tol > 1.0E-8) {
        solution.state = -2;
      }
    }
  } else {
    solution.state = -3;
    totalRank = mTotalWorkingEq_tmp_tmp + 1;
    idxDiag = workingset.nActiveConstr;
    for (nDepInd = totalRank; nDepInd <= idxDiag; nDepInd++) {
      workingset.isActiveConstr = false;
    }
    workingset.nWConstr[2] = 0;
    workingset.nWConstr[3] = 0;
    workingset.nWConstr[4] = 0;
    workingset.nActiveConstr = mTotalWorkingEq_tmp_tmp;
  }
}

} // namespace initialize
} // namespace qpactiveset
} // namespace coder
} // namespace optim
} // namespace coder

//
// File trailer for PresolveWorkingSet.cpp
//
// [EOF]
//
