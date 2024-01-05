//
// File: MPC_Prediction_internal_types.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 05-Jan-2024 13:02:36
//

#ifndef MPC_PREDICTION_INTERNAL_TYPES_H
#define MPC_PREDICTION_INTERNAL_TYPES_H

// Include Files
#include "MPC_Prediction_types.h"
#include "rtwtypes.h"

// Type Definitions
struct struct_T {
  double xstar[11];
  double fstar;
  double firstorderopt;
  double lambda;
  int state;
  double maxConstr;
  int iterations;
  double searchDir[11];
};

struct b_struct_T {
  double grad[11];
  double Hx[10];
  boolean_T hasLinear;
  int nvar;
  int maxVar;
  double beta;
  double rho;
  int objtype;
  int prev_objtype;
  int prev_nvar;
  boolean_T prev_hasLinear;
  double gammaScalar;
};

struct c_struct_T {
  double FMat[121];
  int ldm;
  int ndims;
  int info;
  double scaleFactor;
  boolean_T ConvexCheck;
  double regTol_;
  double workspace_[528];
  double workspace2_[528];
};

struct d_struct_T {
  double workspace_double[121];
  int workspace_int[11];
  int workspace_sort[11];
};

struct e_struct_T {
  int ldq;
  double QR[121];
  double Q[121];
  int jpvt[11];
  int mrows;
  int ncols;
  double tau[11];
  int minRowCol;
  boolean_T usedPivoting;
};

struct f_struct_T {
  int mConstr;
  int mConstrOrig;
  int mConstrMax;
  int nVar;
  int nVarOrig;
  int nVarMax;
  int ldA;
  double lb[11];
  double ub[11];
  int indexLB[11];
  int indexUB[11];
  int indexFixed[11];
  int mEqRemoved;
  double ATwset[11];
  double bwset;
  int nActiveConstr;
  double maxConstrWorkspace;
  int sizes[5];
  int sizesNormal[5];
  int sizesPhaseOne[5];
  int sizesRegularized[5];
  int sizesRegPhaseOne[5];
  int isActiveIdx[6];
  int isActiveIdxNormal[6];
  int isActiveIdxPhaseOne[6];
  int isActiveIdxRegularized[6];
  int isActiveIdxRegPhaseOne[6];
  boolean_T isActiveConstr;
  int Wid;
  int Wlocalidx;
  int nWConstr[5];
  int probType;
  double SLACK0;
};

#endif
//
// File trailer for MPC_Prediction_internal_types.h
//
// [EOF]
//
