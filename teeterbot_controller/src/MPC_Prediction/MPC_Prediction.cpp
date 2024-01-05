//
// File: MPC_Prediction.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 05-Jan-2024 13:02:36
//

// Include Files
#include "MPC_Prediction.h"
#include "MPC_Prediction_internal_types.h"
#include "PresolveWorkingSet.h"
#include "RemoveDependentIneq_.h"
#include "computeFirstOrderOpt.h"
#include "computeFval.h"
#include "feasibleX0ForWorkingSet.h"
#include "iterate.h"
#include "rt_nonfinite.h"
#include "setProblemType.h"
#include <algorithm>
#include <cmath>
#include <cstring>

// Function Definitions
//
// Arguments    : const double x_k[4]
//                const double E[40]
//                const double H[100]
//                double N
//                double p
//                double u_k_data[]
//                int u_k_size[1]
// Return Type  : void
//
void MPC_Prediction(const double x_k[4], const double E[40],
                    const double H[100], double, double p, double u_k_data[],
                    int u_k_size[1])
{
  static const signed char t4_isActiveIdxPhaseOne[6]{1, 1, 1, 1, 2, 2};
  static const signed char t4_isActiveIdxRegPhaseOne[6]{1, 1, 1, 1, 2, 2};
  static const signed char t4_sizesPhaseOne[5]{0, 0, 0, 1, 0};
  static const signed char t4_sizesRegPhaseOne[5]{0, 0, 0, 1, 0};
  b_struct_T objective;
  c_struct_T CholRegManager;
  d_struct_T memspace;
  e_struct_T qrmanager;
  f_struct_T workingset;
  struct_T solution;
  double U_k[10];
  double y[10];
  double H_infnrm;
  double colSum;
  double d;
  double f_infnrm;
  int PROBTYPE_ORIG;
  int i;
  boolean_T okWorkingSet;
  //  NP x 1
  H_infnrm = x_k[0];
  f_infnrm = x_k[1];
  colSum = x_k[2];
  d = x_k[3];
  for (i = 0; i < 10; i++) {
    y[i] = ((E[i] * H_infnrm + E[i + 10] * f_infnrm) + E[i + 20] * colSum) +
           E[i + 30] * d;
  }
  solution.fstar = 0.0;
  solution.firstorderopt = 0.0;
  solution.lambda = 0.0;
  std::memset(&solution.searchDir[0], 0, 11U * sizeof(double));
  CholRegManager.ldm = 11;
  CholRegManager.ndims = 0;
  CholRegManager.info = 0;
  CholRegManager.ConvexCheck = true;
  CholRegManager.regTol_ = 0.0;
  CholRegManager.scaleFactor = 100.0;
  H_infnrm = 0.0;
  f_infnrm = 0.0;
  for (i = 0; i < 10; i++) {
    solution.xstar[i] = 0.0;
    colSum = 0.0;
    for (PROBTYPE_ORIG = 0; PROBTYPE_ORIG < 10; PROBTYPE_ORIG++) {
      colSum += std::abs(H[PROBTYPE_ORIG + 10 * i]);
    }
    H_infnrm = std::fmax(H_infnrm, colSum);
    f_infnrm = std::fmax(f_infnrm, std::abs(y[i]));
  }
  H_infnrm = std::fmax(std::fmax(1.0, f_infnrm), H_infnrm);
  std::memset(&objective.grad[0], 0, 11U * sizeof(double));
  std::memset(&objective.Hx[0], 0, 10U * sizeof(double));
  objective.hasLinear = true;
  objective.nvar = 10;
  objective.maxVar = 11;
  objective.beta = 0.0;
  objective.rho = 0.0;
  objective.objtype = 3;
  objective.prev_objtype = 3;
  objective.prev_nvar = 0;
  objective.prev_hasLinear = false;
  objective.gammaScalar = 0.0;
  solution.state = 82;
  workingset.mConstr = 0;
  workingset.mConstrOrig = 0;
  workingset.mConstrMax = 1;
  workingset.nVar = 10;
  workingset.nVarOrig = 10;
  workingset.nVarMax = 11;
  workingset.ldA = 11;
  workingset.mEqRemoved = 0;
  std::memset(&workingset.lb[0], 0, 11U * sizeof(double));
  std::memset(&workingset.ub[0], 0, 11U * sizeof(double));
  std::memset(&workingset.ATwset[0], 0, 11U * sizeof(double));
  for (i = 0; i < 11; i++) {
    workingset.indexLB[i] = 0;
    workingset.indexUB[i] = 0;
    workingset.indexFixed[i] = 0;
  }
  workingset.bwset = 0.0;
  workingset.nActiveConstr = 0;
  workingset.maxConstrWorkspace = 0.0;
  for (i = 0; i < 5; i++) {
    workingset.sizes[i] = 0;
    workingset.sizesNormal[i] = 0;
    workingset.sizesPhaseOne[i] = t4_sizesPhaseOne[i];
    workingset.sizesRegularized[i] = 0;
    workingset.sizesRegPhaseOne[i] = t4_sizesRegPhaseOne[i];
  }
  for (i = 0; i < 6; i++) {
    workingset.isActiveIdx[i] = 1;
    workingset.isActiveIdxNormal[i] = 1;
    workingset.isActiveIdxPhaseOne[i] = t4_isActiveIdxPhaseOne[i];
    workingset.isActiveIdxRegularized[i] = 1;
    workingset.isActiveIdxRegPhaseOne[i] = t4_isActiveIdxRegPhaseOne[i];
  }
  workingset.isActiveConstr = false;
  workingset.Wid = 0;
  workingset.Wlocalidx = 0;
  for (i = 0; i < 5; i++) {
    workingset.nWConstr[i] = 0;
  }
  workingset.probType = 3;
  workingset.SLACK0 = 0.0;
  qrmanager.ldq = 11;
  std::memset(&qrmanager.QR[0], 0, 121U * sizeof(double));
  std::memset(&qrmanager.Q[0], 0, 121U * sizeof(double));
  qrmanager.mrows = 0;
  qrmanager.ncols = 0;
  std::memset(&qrmanager.tau[0], 0, 11U * sizeof(double));
  for (i = 0; i < 11; i++) {
    qrmanager.jpvt[i] = 0;
  }
  qrmanager.minRowCol = 0;
  qrmanager.usedPivoting = false;
  coder::optim::coder::qpactiveset::initialize::RemoveDependentIneq_(
      workingset, qrmanager, memspace, 100.0);
  okWorkingSet =
      coder::optim::coder::qpactiveset::initialize::feasibleX0ForWorkingSet(
          memspace.workspace_double, solution.xstar, workingset, qrmanager);
  if (!okWorkingSet) {
    coder::optim::coder::qpactiveset::initialize::RemoveDependentIneq_(
        workingset, qrmanager, memspace, 1000.0);
    okWorkingSet =
        coder::optim::coder::qpactiveset::initialize::feasibleX0ForWorkingSet(
            memspace.workspace_double, solution.xstar, workingset, qrmanager);
    if (!okWorkingSet) {
      solution.state = -7;
    }
  }
  if (solution.state >= 0) {
    solution.iterations = 0;
    solution.maxConstr = 0.0;
    coder::optim::coder::qpactiveset::iterate(
        H, y, solution, memspace, workingset, qrmanager, CholRegManager,
        objective, -1.0E+20, 1.0E-8, H_infnrm, true);
    if (solution.state != -6) {
      f_infnrm = 0.0;
      if (workingset.sizes[3] > 0) {
        f_infnrm = std::fmax(0.0, -solution.xstar[workingset.indexLB[0] - 1]);
      }
      solution.maxConstr = f_infnrm;
      coder::optim::coder::qpactiveset::parseoutput::computeFirstOrderOpt(
          solution, objective, workingset.nVar, workingset.ATwset,
          workingset.nActiveConstr, memspace.workspace_double);
      while ((solution.iterations < 100) &&
             ((solution.state == -7) ||
              ((solution.state == 1) &&
               ((solution.maxConstr > 1.0E-8) ||
                (solution.firstorderopt > 1.0E-8 * H_infnrm))))) {
        int nVar;
        coder::optim::coder::qpactiveset::initialize::feasibleX0ForWorkingSet(
            memspace.workspace_double, solution.xstar, workingset, qrmanager);
        coder::optim::coder::qpactiveset::initialize::PresolveWorkingSet(
            solution, memspace, workingset, qrmanager);
        PROBTYPE_ORIG = workingset.probType;
        nVar = workingset.nVar;
        solution.xstar[10] = solution.maxConstr + 1.0;
        if (workingset.probType == 3) {
          i = 1;
        } else {
          i = 4;
        }
        coder::optim::coder::qpactiveset::WorkingSet::setProblemType(workingset,
                                                                     i);
        i = workingset.nWConstr[0] + workingset.nWConstr[1];
        if (i + 1 <= workingset.nActiveConstr) {
          workingset.isActiveConstr = false;
        }
        workingset.nWConstr[2] = 0;
        workingset.nWConstr[3] = 0;
        workingset.nWConstr[4] = 0;
        workingset.nActiveConstr = i;
        objective.prev_objtype = objective.objtype;
        objective.prev_nvar = objective.nvar;
        objective.prev_hasLinear = objective.hasLinear;
        objective.objtype = 5;
        objective.nvar = 11;
        objective.gammaScalar = 1.0;
        objective.hasLinear = true;
        solution.fstar =
            coder::optim::coder::qpactiveset::Objective::computeFval(
                objective, memspace.workspace_double, H, y, solution.xstar);
        solution.state = 5;
        coder::optim::coder::qpactiveset::iterate(
            H, y, solution, memspace, workingset, qrmanager, CholRegManager,
            objective, 1.0E-8, 1.4901161193847657E-10, H_infnrm, false);
        if (workingset.isActiveConstr) {
          boolean_T exitg1;
          i = 1;
          exitg1 = false;
          while ((!exitg1) && (i <= workingset.nActiveConstr)) {
            if ((workingset.Wid == 4) &&
                (workingset.Wlocalidx == workingset.sizes[3])) {
              workingset.isActiveConstr = false;
              workingset.bwset = 0.0;
              workingset.nActiveConstr--;
              workingset.nWConstr[3]--;
              exitg1 = true;
            } else {
              i = 2;
            }
          }
        }
        i = workingset.nActiveConstr;
        while ((i > 0) && (i > nVar)) {
          workingset.isActiveConstr = false;
          workingset.bwset = 0.0;
          workingset.nActiveConstr--;
          workingset.nWConstr[workingset.Wid - 1]--;
          i = 0;
        }
        solution.maxConstr = solution.xstar[10];
        coder::optim::coder::qpactiveset::WorkingSet::setProblemType(
            workingset, PROBTYPE_ORIG);
        objective.objtype = objective.prev_objtype;
        objective.nvar = objective.prev_nvar;
        objective.hasLinear = objective.prev_hasLinear;
        coder::optim::coder::qpactiveset::iterate(
            H, y, solution, memspace, workingset, qrmanager, CholRegManager,
            objective, -1.0E+20, 1.0E-8, H_infnrm, false);
        f_infnrm = 0.0;
        if (workingset.sizes[3] > 0) {
          f_infnrm = std::fmax(0.0, -solution.xstar[workingset.indexLB[0] - 1]);
        }
        solution.maxConstr = f_infnrm;
        coder::optim::coder::qpactiveset::parseoutput::computeFirstOrderOpt(
            solution, objective, workingset.nVar, workingset.ATwset,
            workingset.nActiveConstr, memspace.workspace_double);
      }
    }
  }
  std::copy(&solution.xstar[0], &solution.xstar[10], &U_k[0]);
  if (solution.state <= 0) {
    coder::optim::coder::qpactiveset::Objective::computeFval(
        objective, memspace.workspace_double, H, y, solution.xstar);
  }
  if (p < 1.0) {
    i = 0;
  } else {
    i = static_cast<int>(p);
  }
  u_k_size[0] = i;
  if (i - 1 >= 0) {
    std::copy(&U_k[0], &U_k[i], &u_k_data[0]);
  }
}

//
// File trailer for MPC_Prediction.cpp
//
// [EOF]
//
