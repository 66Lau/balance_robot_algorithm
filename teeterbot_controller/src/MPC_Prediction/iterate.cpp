//
// File: iterate.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 05-Jan-2024 13:02:36
//

// Include Files
#include "iterate.h"
#include "MPC_Prediction_internal_types.h"
#include "MPC_Prediction_rtwutil.h"
#include "addBoundToActiveSetMatrix_.h"
#include "checkStoppingAndUpdateFval.h"
#include "computeFval_ReuseHx.h"
#include "computeGrad_StoreHx.h"
#include "computeQ_.h"
#include "compute_deltax.h"
#include "compute_lambda.h"
#include "deleteColMoveEnd.h"
#include "factorQR.h"
#include "rt_nonfinite.h"
#include "xnrm2.h"
#include "xrotg.h"
#include <cmath>
#include <cstring>

// Function Definitions
//
// Arguments    : const double H[100]
//                const double f[10]
//                struct_T &solution
//                d_struct_T &memspace
//                f_struct_T &workingset
//                e_struct_T &qrmanager
//                c_struct_T &cholmanager
//                b_struct_T &objective
//                double options_ObjectiveLimit
//                double options_StepTolerance
//                double runTimeOptions_ProbRelTolFactor
//                boolean_T runTimeOptions_RemainFeasible
// Return Type  : void
//
namespace coder {
namespace optim {
namespace coder {
namespace qpactiveset {
void iterate(const double H[100], const double f[10], struct_T &solution,
             d_struct_T &memspace, f_struct_T &workingset,
             e_struct_T &qrmanager, c_struct_T &cholmanager,
             b_struct_T &objective, double options_ObjectiveLimit,
             double options_StepTolerance,
             double runTimeOptions_ProbRelTolFactor,
             boolean_T runTimeOptions_RemainFeasible)
{
  double d;
  double s;
  double tolDelta;
  int TYPE;
  int activeSetChangeID;
  int globalActiveConstrIdx;
  int nVar;
  boolean_T subProblemChanged;
  boolean_T updateFval;
  subProblemChanged = true;
  updateFval = true;
  activeSetChangeID = 0;
  TYPE = objective.objtype;
  tolDelta = 6.7434957617430445E-7;
  nVar = workingset.nVar;
  globalActiveConstrIdx = 0;
  Objective::computeGrad_StoreHx(objective, H, f, solution.xstar);
  solution.fstar = Objective::computeFval_ReuseHx(
      objective, memspace.workspace_double, f, solution.xstar);
  if (solution.iterations < 100) {
    solution.state = -5;
  } else {
    solution.state = 0;
  }
  solution.lambda = 0.0;
  int exitg1;
  do {
    exitg1 = 0;
    if (solution.state == -5) {
      double ratio;
      int Qk0;
      int i;
      int iyend;
      boolean_T guard1{false};
      guard1 = false;
      if (subProblemChanged) {
        double c;
        double temp;
        switch (activeSetChangeID) {
        case 1: {
          int ix0;
          ix0 = 11 * (workingset.nActiveConstr - 1);
          iyend = qrmanager.mrows;
          Qk0 = qrmanager.ncols + 1;
          if (iyend <= Qk0) {
            Qk0 = iyend;
          }
          qrmanager.minRowCol = Qk0;
          Qk0 = 11 * qrmanager.ncols;
          if (qrmanager.mrows != 0) {
            iyend = Qk0 + qrmanager.mrows;
            if (Qk0 + 1 <= iyend) {
              std::memset(&qrmanager.QR[Qk0], 0,
                          static_cast<unsigned int>(iyend - Qk0) *
                              sizeof(double));
            }
            i = 11 * (qrmanager.mrows - 1) + 1;
            for (int iac{1}; iac <= i; iac += 11) {
              c = 0.0;
              iyend = (iac + qrmanager.mrows) - 1;
              for (int idx{iac}; idx <= iyend; idx++) {
                c +=
                    qrmanager.Q[idx - 1] * workingset.ATwset[(ix0 + idx) - iac];
              }
              iyend = Qk0 + div_nde_s32_floor(iac - 1);
              qrmanager.QR[iyend] += c;
            }
          }
          qrmanager.ncols++;
          i = qrmanager.ncols - 1;
          qrmanager.jpvt[i] = qrmanager.ncols;
          for (int idx{qrmanager.mrows - 2}; idx + 2 > qrmanager.ncols; idx--) {
            iyend = idx + 11 * i;
            d = qrmanager.QR[iyend + 1];
            c = internal::blas::xrotg(qrmanager.QR[iyend], d, s);
            qrmanager.QR[iyend + 1] = d;
            Qk0 = 11 * idx;
            iyend = qrmanager.mrows;
            if (qrmanager.mrows >= 1) {
              for (int iac{0}; iac < iyend; iac++) {
                ix0 = Qk0 + iac;
                ratio = qrmanager.Q[ix0 + 11];
                temp = c * qrmanager.Q[ix0] + s * ratio;
                qrmanager.Q[ix0 + 11] = c * ratio - s * qrmanager.Q[ix0];
                qrmanager.Q[ix0] = temp;
              }
            }
          }
        } break;
        case -1:
          QRManager::deleteColMoveEnd(qrmanager, globalActiveConstrIdx);
          break;
        default:
          QRManager::factorQR(qrmanager, workingset.ATwset, nVar,
                              workingset.nActiveConstr);
          QRManager::computeQ_(qrmanager, qrmanager.mrows);
          break;
        }
        compute_deltax(H, solution, memspace, qrmanager, cholmanager,
                       objective);
        if (solution.state != -5) {
          exitg1 = 1;
        } else if ((internal::blas::xnrm2(nVar, solution.searchDir) <
                    options_StepTolerance) ||
                   (workingset.nActiveConstr >= nVar)) {
          guard1 = true;
        } else {
          boolean_T newBlocking;
          updateFval = (TYPE == 5);
          if (updateFval || runTimeOptions_RemainFeasible) {
            c = 1.0E+30;
            newBlocking = false;
            iyend = 0;
            Qk0 = 0;
            if (workingset.nWConstr[3] < workingset.sizes[3]) {
              d = -solution.searchDir[workingset.indexLB[0] - 1];
              if ((d > 2.2204460492503131E-13 *
                           internal::blas::xnrm2(workingset.nVar,
                                                 solution.searchDir)) &&
                  (!workingset.isActiveConstr)) {
                ratio = -solution.xstar[workingset.indexLB[0] - 1];
                ratio = std::fmin(std::abs(ratio), 1.0E-8 - ratio) / d;
                if (ratio < 1.0E+30) {
                  c = ratio;
                  iyend = 4;
                  Qk0 = 1;
                  newBlocking = true;
                }
              }
            }
            if (!updateFval) {
              if (newBlocking && (c > 1.0)) {
                newBlocking = false;
              }
              c = std::fmin(c, 1.0);
            }
          } else {
            c = 1.0E+30;
            newBlocking = false;
            iyend = 0;
            Qk0 = 0;
            temp = 0.0;
            if (workingset.nWConstr[3] < workingset.sizes[3]) {
              d = -solution.searchDir[workingset.indexLB[0] - 1];
              if ((d > 2.2204460492503131E-13 *
                           internal::blas::xnrm2(workingset.nVar,
                                                 solution.searchDir)) &&
                  (!workingset.isActiveConstr)) {
                ratio = -solution.xstar[workingset.indexLB[0] - 1] - tolDelta;
                ratio = std::fmin(std::abs(ratio), 1.0E-8 - ratio) / d;
                if ((ratio <= 1.0E+30) &&
                    (std::abs(solution.searchDir[workingset.indexLB[0] - 1]) >
                     0.0)) {
                  c = ratio;
                  iyend = 4;
                  Qk0 = 1;
                  newBlocking = true;
                }
                ratio =
                    std::fmin(
                        std::abs(-solution.xstar[workingset.indexLB[0] - 1]),
                        1.0E-8 - (-solution.xstar[workingset.indexLB[0] - 1])) /
                    -solution.searchDir[workingset.indexLB[0] - 1];
                if (ratio < c) {
                  c = ratio;
                  iyend = 4;
                  Qk0 = 1;
                  newBlocking = true;
                  temp =
                      std::abs(solution.searchDir[workingset.indexLB[0] - 1]);
                }
              }
            }
            tolDelta += 6.608625846508183E-7;
            if (temp > 0.0) {
              c = std::fmax(c, 6.608625846508183E-7 / temp);
            }
            if (newBlocking && (c > 1.0)) {
              newBlocking = false;
            }
            c = std::fmin(c, 1.0);
          }
          if (newBlocking) {
            switch (iyend) {
            case 3:
              workingset.nWConstr[2]++;
              workingset.isActiveConstr = true;
              workingset.nActiveConstr++;
              workingset.Wid = 3;
              workingset.Wlocalidx = Qk0;
              // A check that is always false is detected at compile-time.
              // Eliminating code that follows.
              break;
            case 4:
              WorkingSet::addBoundToActiveSetMatrix_(workingset, 4, Qk0);
              break;
            default:
              WorkingSet::addBoundToActiveSetMatrix_(workingset, 5, Qk0);
              break;
            }
            activeSetChangeID = 1;
          } else {
            if (objective.objtype == 5) {
              if (internal::blas::xnrm2(objective.nvar, solution.searchDir) >
                  100.0 * static_cast<double>(objective.nvar) *
                      1.4901161193847656E-8) {
                solution.state = 3;
              } else {
                solution.state = 4;
              }
            }
            subProblemChanged = false;
            if (workingset.nActiveConstr == 0) {
              solution.state = 1;
            }
          }
          if (!(c == 0.0)) {
            iyend = nVar - 1;
            for (int iac{0}; iac <= iyend; iac++) {
              solution.xstar[iac] += c * solution.searchDir[iac];
            }
          }
          Objective::computeGrad_StoreHx(objective, H, f, solution.xstar);
          updateFval = true;
          stopping::checkStoppingAndUpdateFval(
              activeSetChangeID, f, solution, memspace, objective, workingset,
              qrmanager, options_ObjectiveLimit, updateFval);
        }
      } else {
        i = static_cast<unsigned char>(nVar);
        std::memset(&solution.searchDir[0], 0,
                    static_cast<unsigned int>(i) * sizeof(double));
        guard1 = true;
      }
      if (guard1) {
        compute_lambda(memspace.workspace_double, solution, objective,
                       qrmanager);
        if ((solution.state != -7) || (workingset.nActiveConstr > nVar)) {
          Qk0 = 0;
          ratio = 0.0 * runTimeOptions_ProbRelTolFactor *
                  static_cast<double>(TYPE != 5);
          i = (workingset.nWConstr[0] + workingset.nWConstr[1]) + 1;
          iyend = workingset.nActiveConstr;
          for (int idx{i}; idx <= iyend; idx++) {
            if (solution.lambda < ratio) {
              ratio = solution.lambda;
              Qk0 = 1;
            }
          }
          if (Qk0 == 0) {
            solution.state = 1;
          } else {
            activeSetChangeID = -1;
            globalActiveConstrIdx = 1;
            subProblemChanged = true;
            workingset.isActiveConstr = false;
            workingset.bwset = 0.0;
            workingset.nActiveConstr--;
            i = workingset.Wid - 1;
            workingset.nWConstr[i]--;
            solution.lambda = 0.0;
          }
        } else {
          activeSetChangeID = 0;
          globalActiveConstrIdx = workingset.nActiveConstr;
          subProblemChanged = true;
          workingset.isActiveConstr = false;
          workingset.bwset = 0.0;
          workingset.nActiveConstr--;
          i = workingset.Wid - 1;
          workingset.nWConstr[i]--;
          solution.lambda = 0.0;
        }
        updateFval = false;
        stopping::checkStoppingAndUpdateFval(
            activeSetChangeID, f, solution, memspace, objective, workingset,
            qrmanager, options_ObjectiveLimit, updateFval);
      }
    } else {
      if (!updateFval) {
        solution.fstar = Objective::computeFval_ReuseHx(
            objective, memspace.workspace_double, f, solution.xstar);
      }
      exitg1 = 1;
    }
  } while (exitg1 == 0);
}

} // namespace qpactiveset
} // namespace coder
} // namespace optim
} // namespace coder

//
// File trailer for iterate.cpp
//
// [EOF]
//
