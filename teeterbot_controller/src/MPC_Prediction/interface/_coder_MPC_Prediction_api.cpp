//
// File: _coder_MPC_Prediction_api.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 05-Jan-2024 13:02:36
//

// Include Files
#include "_coder_MPC_Prediction_api.h"
#include "_coder_MPC_Prediction_mex.h"

// Variable Definitions
emlrtCTX emlrtRootTLSGlobal{nullptr};

emlrtContext emlrtContextGlobal{
    true,                                                 // bFirstTime
    false,                                                // bInitialized
    131642U,                                              // fVersionInfo
    nullptr,                                              // fErrorFunction
    "MPC_Prediction",                                     // fFunctionName
    nullptr,                                              // fRTCallStack
    false,                                                // bDebugMode
    {2045744189U, 2170104910U, 2743257031U, 4284093946U}, // fSigWrd
    nullptr                                               // fSigMem
};

// Function Declarations
static real_T (*b_emlrt_marshallIn(const emlrtStack &sp, const mxArray *E,
                                   const char_T *identifier))[40];

static real_T (*b_emlrt_marshallIn(const emlrtStack &sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[40];

static real_T (*c_emlrt_marshallIn(const emlrtStack &sp, const mxArray *H,
                                   const char_T *identifier))[100];

static real_T (*c_emlrt_marshallIn(const emlrtStack &sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[100];

static real_T d_emlrt_marshallIn(const emlrtStack &sp, const mxArray *N,
                                 const char_T *identifier);

static real_T d_emlrt_marshallIn(const emlrtStack &sp, const mxArray *u,
                                 const emlrtMsgIdentifier *parentId);

static real_T (*e_emlrt_marshallIn(const emlrtStack &sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[4];

static real_T (*emlrt_marshallIn(const emlrtStack &sp, const mxArray *x_k,
                                 const char_T *identifier))[4];

static real_T (*emlrt_marshallIn(const emlrtStack &sp, const mxArray *u,
                                 const emlrtMsgIdentifier *parentId))[4];

static const mxArray *emlrt_marshallOut(const real_T u_data[],
                                        const int32_T &u_size);

static real_T (*f_emlrt_marshallIn(const emlrtStack &sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[40];

static real_T (*g_emlrt_marshallIn(const emlrtStack &sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[100];

static real_T h_emlrt_marshallIn(const emlrtStack &sp, const mxArray *src,
                                 const emlrtMsgIdentifier *msgId);

// Function Definitions
//
// Arguments    : const emlrtStack &sp
//                const mxArray *E
//                const char_T *identifier
// Return Type  : real_T (*)[40]
//
static real_T (*b_emlrt_marshallIn(const emlrtStack &sp, const mxArray *E,
                                   const char_T *identifier))[40]
{
  emlrtMsgIdentifier thisId;
  real_T(*y)[40];
  thisId.fIdentifier = const_cast<const char_T *>(identifier);
  thisId.fParent = nullptr;
  thisId.bParentIsCell = false;
  y = b_emlrt_marshallIn(sp, emlrtAlias(E), &thisId);
  emlrtDestroyArray(&E);
  return y;
}

//
// Arguments    : const emlrtStack &sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
// Return Type  : real_T (*)[40]
//
static real_T (*b_emlrt_marshallIn(const emlrtStack &sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[40]
{
  real_T(*y)[40];
  y = f_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

//
// Arguments    : const emlrtStack &sp
//                const mxArray *H
//                const char_T *identifier
// Return Type  : real_T (*)[100]
//
static real_T (*c_emlrt_marshallIn(const emlrtStack &sp, const mxArray *H,
                                   const char_T *identifier))[100]
{
  emlrtMsgIdentifier thisId;
  real_T(*y)[100];
  thisId.fIdentifier = const_cast<const char_T *>(identifier);
  thisId.fParent = nullptr;
  thisId.bParentIsCell = false;
  y = c_emlrt_marshallIn(sp, emlrtAlias(H), &thisId);
  emlrtDestroyArray(&H);
  return y;
}

//
// Arguments    : const emlrtStack &sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
// Return Type  : real_T (*)[100]
//
static real_T (*c_emlrt_marshallIn(const emlrtStack &sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[100]
{
  real_T(*y)[100];
  y = g_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

//
// Arguments    : const emlrtStack &sp
//                const mxArray *N
//                const char_T *identifier
// Return Type  : real_T
//
static real_T d_emlrt_marshallIn(const emlrtStack &sp, const mxArray *N,
                                 const char_T *identifier)
{
  emlrtMsgIdentifier thisId;
  real_T y;
  thisId.fIdentifier = const_cast<const char_T *>(identifier);
  thisId.fParent = nullptr;
  thisId.bParentIsCell = false;
  y = d_emlrt_marshallIn(sp, emlrtAlias(N), &thisId);
  emlrtDestroyArray(&N);
  return y;
}

//
// Arguments    : const emlrtStack &sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
// Return Type  : real_T
//
static real_T d_emlrt_marshallIn(const emlrtStack &sp, const mxArray *u,
                                 const emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = h_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

//
// Arguments    : const emlrtStack &sp
//                const mxArray *src
//                const emlrtMsgIdentifier *msgId
// Return Type  : real_T (*)[4]
//
static real_T (*e_emlrt_marshallIn(const emlrtStack &sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[4]
{
  static const int32_T dims{4};
  real_T(*ret)[4];
  int32_T i;
  boolean_T b{false};
  emlrtCheckVsBuiltInR2012b((emlrtConstCTX)&sp, msgId, src, "double", false, 1U,
                            (const void *)&dims, &b, &i);
  ret = (real_T(*)[4])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

//
// Arguments    : const emlrtStack &sp
//                const mxArray *x_k
//                const char_T *identifier
// Return Type  : real_T (*)[4]
//
static real_T (*emlrt_marshallIn(const emlrtStack &sp, const mxArray *x_k,
                                 const char_T *identifier))[4]
{
  emlrtMsgIdentifier thisId;
  real_T(*y)[4];
  thisId.fIdentifier = const_cast<const char_T *>(identifier);
  thisId.fParent = nullptr;
  thisId.bParentIsCell = false;
  y = emlrt_marshallIn(sp, emlrtAlias(x_k), &thisId);
  emlrtDestroyArray(&x_k);
  return y;
}

//
// Arguments    : const emlrtStack &sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
// Return Type  : real_T (*)[4]
//
static real_T (*emlrt_marshallIn(const emlrtStack &sp, const mxArray *u,
                                 const emlrtMsgIdentifier *parentId))[4]
{
  real_T(*y)[4];
  y = e_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

//
// Arguments    : const real_T u_data[]
//                const int32_T &u_size
// Return Type  : const mxArray *
//
static const mxArray *emlrt_marshallOut(const real_T u_data[],
                                        const int32_T &u_size)
{
  static const int32_T i{0};
  const mxArray *m;
  const mxArray *y;
  y = nullptr;
  m = emlrtCreateNumericArray(1, (const void *)&i, mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, (void *)&u_data[0]);
  emlrtSetDimensions((mxArray *)m, &u_size, 1);
  emlrtAssign(&y, m);
  return y;
}

//
// Arguments    : const emlrtStack &sp
//                const mxArray *src
//                const emlrtMsgIdentifier *msgId
// Return Type  : real_T (*)[40]
//
static real_T (*f_emlrt_marshallIn(const emlrtStack &sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[40]
{
  static const int32_T dims[2]{10, 4};
  real_T(*ret)[40];
  int32_T iv[2];
  boolean_T bv[2]{false, false};
  emlrtCheckVsBuiltInR2012b((emlrtConstCTX)&sp, msgId, src, "double", false, 2U,
                            (const void *)&dims[0], &bv[0], &iv[0]);
  ret = (real_T(*)[40])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

//
// Arguments    : const emlrtStack &sp
//                const mxArray *src
//                const emlrtMsgIdentifier *msgId
// Return Type  : real_T (*)[100]
//
static real_T (*g_emlrt_marshallIn(const emlrtStack &sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[100]
{
  static const int32_T dims[2]{10, 10};
  real_T(*ret)[100];
  int32_T iv[2];
  boolean_T bv[2]{false, false};
  emlrtCheckVsBuiltInR2012b((emlrtConstCTX)&sp, msgId, src, "double", false, 2U,
                            (const void *)&dims[0], &bv[0], &iv[0]);
  ret = (real_T(*)[100])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

//
// Arguments    : const emlrtStack &sp
//                const mxArray *src
//                const emlrtMsgIdentifier *msgId
// Return Type  : real_T
//
static real_T h_emlrt_marshallIn(const emlrtStack &sp, const mxArray *src,
                                 const emlrtMsgIdentifier *msgId)
{
  static const int32_T dims{0};
  real_T ret;
  emlrtCheckBuiltInR2012b((emlrtConstCTX)&sp, msgId, src, "double", false, 0U,
                          (const void *)&dims);
  ret = *static_cast<real_T *>(emlrtMxGetData(src));
  emlrtDestroyArray(&src);
  return ret;
}

//
// Arguments    : const mxArray * const prhs[5]
//                const mxArray **plhs
// Return Type  : void
//
void MPC_Prediction_api(const mxArray *const prhs[5], const mxArray **plhs)
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  real_T(*H)[100];
  real_T(*E)[40];
  real_T(*u_k_data)[10];
  real_T(*x_k)[4];
  real_T N;
  real_T p;
  int32_T u_k_size;
  st.tls = emlrtRootTLSGlobal;
  u_k_data = (real_T(*)[10])mxMalloc(sizeof(real_T[10]));
  // Marshall function inputs
  x_k = emlrt_marshallIn(st, emlrtAlias(prhs[0]), "x_k");
  E = b_emlrt_marshallIn(st, emlrtAlias(prhs[1]), "E");
  H = c_emlrt_marshallIn(st, emlrtAlias(prhs[2]), "H");
  N = d_emlrt_marshallIn(st, emlrtAliasP(prhs[3]), "N");
  p = d_emlrt_marshallIn(st, emlrtAliasP(prhs[4]), "p");
  // Invoke the target function
  MPC_Prediction(*x_k, *E, *H, N, p, *u_k_data, *(int32_T(*)[1]) & u_k_size);
  // Marshall function outputs
  *plhs = emlrt_marshallOut(*u_k_data, u_k_size);
}

//
// Arguments    : void
// Return Type  : void
//
void MPC_Prediction_atexit()
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  MPC_Prediction_xil_terminate();
  MPC_Prediction_xil_shutdown();
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

//
// Arguments    : void
// Return Type  : void
//
void MPC_Prediction_initialize()
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, nullptr);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

//
// Arguments    : void
// Return Type  : void
//
void MPC_Prediction_terminate()
{
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

//
// File trailer for _coder_MPC_Prediction_api.cpp
//
// [EOF]
//
