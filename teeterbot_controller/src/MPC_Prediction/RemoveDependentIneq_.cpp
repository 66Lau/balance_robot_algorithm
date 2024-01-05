//
// File: RemoveDependentIneq_.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 05-Jan-2024 13:02:36
//

// Include Files
#include "RemoveDependentIneq_.h"
#include "MPC_Prediction_internal_types.h"
#include "countsort.h"
#include "factorQRE.h"
#include "rt_nonfinite.h"
#include <algorithm>
#include <cmath>
#include <cstring>

// Function Definitions
//
// Arguments    : f_struct_T &workingset
//                e_struct_T &qrmanager
//                d_struct_T &memspace
//                double tolfactor
// Return Type  : void
//
namespace coder {
namespace optim {
namespace coder {
namespace qpactiveset {
namespace initialize {
void RemoveDependentIneq_(f_struct_T &workingset, e_struct_T &qrmanager,
                          d_struct_T &memspace, double tolfactor)
{
  int nDepIneq;
  int nFixedConstr;
  int nVar;
  nDepIneq = workingset.nActiveConstr;
  nFixedConstr = workingset.nWConstr[0] + workingset.nWConstr[1];
  nVar = workingset.nVar;
  if ((workingset.nWConstr[2] + workingset.nWConstr[3]) +
          workingset.nWConstr[4] >
      0) {
    double tol;
    int i;
    int idx;
    int idxDiag;
    tol = tolfactor * static_cast<double>(workingset.nVar) *
          2.2204460492503131E-16;
    for (idx = 0; idx < nFixedConstr; idx++) {
      qrmanager.jpvt[idx] = 1;
    }
    i = nFixedConstr + 1;
    if (i <= nDepIneq) {
      std::memset(&qrmanager.jpvt[i + -1], 0,
                  static_cast<unsigned int>((nDepIneq - i) + 1) * sizeof(int));
    }
    for (idx = 0; idx < nDepIneq; idx++) {
      idxDiag = 11 * idx;
      i = static_cast<unsigned char>(nVar);
      std::copy(&workingset.ATwset[idxDiag],
                &workingset.ATwset[idxDiag + ((i + idxDiag) - idxDiag)],
                &qrmanager.QR[idxDiag]);
    }
    QRManager::factorQRE(qrmanager, workingset.nVar, workingset.nActiveConstr);
    nDepIneq = 0;
    idx = workingset.nActiveConstr;
    while (idx > nVar) {
      nDepIneq++;
      memspace.workspace_int[nDepIneq - 1] = qrmanager.jpvt[10];
      idx = 10;
    }
    if (idx <= workingset.nVar) {
      idxDiag = idx + 11 * (idx - 1);
      while ((idx > nFixedConstr) &&
             (std::abs(qrmanager.QR[idxDiag - 1]) < tol)) {
        nDepIneq++;
        memspace.workspace_int[nDepIneq - 1] = qrmanager.jpvt[idx - 1];
        idx--;
        idxDiag -= 12;
      }
    }
    utils::countsort(memspace.workspace_int, nDepIneq, memspace.workspace_sort,
                     nFixedConstr + 1, workingset.nActiveConstr);
    for (idx = nDepIneq; idx >= 1; idx--) {
      workingset.isActiveConstr = false;
      workingset.bwset = 0.0;
      workingset.nActiveConstr--;
      i = workingset.Wid - 1;
      workingset.nWConstr[i]--;
    }
  }
}

} // namespace initialize
} // namespace qpactiveset
} // namespace coder
} // namespace optim
} // namespace coder

//
// File trailer for RemoveDependentIneq_.cpp
//
// [EOF]
//
