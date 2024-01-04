//
// File: MPC_Matrices.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 04-Jan-2024 19:50:21
//

// Include Files
#include "MPC_Matrices.h"
#include "coder_array.h"
#include <algorithm>
#include <cstring>

// Function Declarations
static void plus(coder::array<double, 2U> &in1,
                 const coder::array<double, 2U> &in2);

// Function Definitions
//
// Arguments    : coder::array<double, 2U> &in1
//                const coder::array<double, 2U> &in2
// Return Type  : void
//
static void plus(coder::array<double, 2U> &in1,
                 const coder::array<double, 2U> &in2)
{
  coder::array<double, 2U> b_in1;
  int aux_0_1;
  int aux_1_1;
  int b_loop_ub;
  int loop_ub;
  int stride_0_0;
  int stride_0_1;
  int stride_1_0;
  int stride_1_1;
  if (in2.size(0) == 1) {
    loop_ub = in1.size(0);
  } else {
    loop_ub = in2.size(0);
  }
  if (in2.size(1) == 1) {
    b_loop_ub = in1.size(1);
  } else {
    b_loop_ub = in2.size(1);
  }
  b_in1.set_size(loop_ub, b_loop_ub);
  stride_0_0 = (in1.size(0) != 1);
  stride_0_1 = (in1.size(1) != 1);
  stride_1_0 = (in2.size(0) != 1);
  stride_1_1 = (in2.size(1) != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (int i{0}; i < b_loop_ub; i++) {
    for (int i1{0}; i1 < loop_ub; i1++) {
      b_in1[i1 + b_in1.size(0) * i] =
          in1[i1 * stride_0_0 + in1.size(0) * aux_0_1] +
          in2[i1 * stride_1_0 + in2.size(0) * aux_1_1];
    }
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
  in1.set_size(b_in1.size(0), b_in1.size(1));
  loop_ub = b_in1.size(1);
  for (int i{0}; i < loop_ub; i++) {
    b_loop_ub = b_in1.size(0);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
      in1[i1 + in1.size(0) * i] = b_in1[i1 + b_in1.size(0) * i];
    }
  }
}

//
// Arguments    : const double A[16]
//                const double B[4]
//                const double Q[16]
//                double R
//                const double F[16]
//                double N
//                coder::array<double, 2U> &E
//                coder::array<double, 2U> &H
// Return Type  : void
//
void MPC_Matrices(const double A[16], const double B[4], const double Q[16],
                  double R, const double F[16], double N,
                  coder::array<double, 2U> &E, coder::array<double, 2U> &H)
{
  coder::array<double, 2U> C;
  coder::array<double, 2U> M;
  coder::array<double, 2U> Q_bar;
  coder::array<double, 2U> R_bar;
  coder::array<double, 2U> b_tmp;
  coder::array<double, 2U> varargin_1;
  coder::array<signed char, 2U> A_tmp;
  double b_A[16];
  double tmp[16];
  double bkj;
  double d;
  double d1;
  double d2;
  double d3;
  int aoffset;
  int boffset;
  int coffset;
  int i;
  int j;
  int kidx;
  int loop_ub_tmp;
  int ma;
  int na;
  //  A 是 n x n 矩阵, 得到 n
  //  B 是 n x p 矩阵, 得到 p
  // %%%%%%%%%%%
  std::memset(&tmp[0], 0, 16U * sizeof(double));
  tmp[0] = 1.0;
  tmp[5] = 1.0;
  tmp[10] = 1.0;
  tmp[15] = 1.0;
  na = static_cast<int>(N * 4.0);
  M.set_size(na + 4, 4);
  for (i = 0; i < 4; i++) {
    ma = i << 2;
    M[M.size(0) * i] = tmp[ma];
    M[M.size(0) * i + 1] = tmp[ma + 1];
    M[M.size(0) * i + 2] = tmp[ma + 2];
    M[M.size(0) * i + 3] = tmp[ma + 3];
    for (j = 0; j < na; j++) {
      M[(j + M.size(0) * i) + 4] = 0.0;
    }
  }
  //  初始化 M 矩阵. M 矩阵是 (N+1)n x n的， 
  //  它上面是 n x n 个 "I", 这一步先把下半部
  //  分写成 0 
  i = static_cast<int>((N + 1.0) * 4.0);
  j = static_cast<int>(N);
  C.set_size(i, j);
  na = i * static_cast<int>(N);
  for (i = 0; i < na; i++) {
    C[i] = 0.0;
  }
  //  初始化 C 矩阵, 这一步令它有 (N+1)n x NP 个 0
  //  定义M 和 C 
  // 定义一个n x n 的 I 矩阵
  // 　更新Ｍ和C
  if (j - 1 >= 0) {
    d = B[0];
    d1 = B[1];
    d2 = B[2];
    d3 = B[3];
  }
  for (int b_i{0}; b_i < j; b_i++) {
    double rows[4];
    double d4;
    double d5;
    double d6;
    //  循环，i 从 1到 N
    bkj = (static_cast<double>(b_i) + 1.0) * 4.0;
    // 定义当前行数，从i x n开始，共n行 
    if (C.size(1) - 1 < 1) {
      na = 1;
    } else {
      na = C.size(1);
    }
    b_tmp.set_size(4, na);
    for (i = 0; i < 4; i++) {
      rows[i] = bkj + (static_cast<double>(i) + 1.0);
      b_tmp[i] =
          ((tmp[i] * d + tmp[i + 4] * d1) + tmp[i + 8] * d2) + tmp[i + 12] * d3;
    }
    for (i = 0; i <= na - 2; i++) {
      b_tmp[4 * (i + 1)] =
          C[(static_cast<int>(rows[0] - 4.0) + C.size(0) * i) - 1];
      b_tmp[4 * (i + 1) + 1] =
          C[(static_cast<int>(rows[1] - 4.0) + C.size(0) * i) - 1];
      b_tmp[4 * (i + 1) + 2] =
          C[(static_cast<int>(rows[2] - 4.0) + C.size(0) * i) - 1];
      b_tmp[4 * (i + 1) + 3] =
          C[(static_cast<int>(rows[3] - 4.0) + C.size(0) * i) - 1];
    }
    na = b_tmp.size(1);
    for (i = 0; i < na; i++) {
      C[(static_cast<int>(rows[0]) + C.size(0) * i) - 1] = b_tmp[4 * i];
      C[(static_cast<int>(rows[1]) + C.size(0) * i) - 1] = b_tmp[4 * i + 1];
      C[(static_cast<int>(rows[2]) + C.size(0) * i) - 1] = b_tmp[4 * i + 2];
      C[(static_cast<int>(rows[3]) + C.size(0) * i) - 1] = b_tmp[4 * i + 3];
    }
    // 将c矩阵填满
    for (i = 0; i < 4; i++) {
      bkj = A[i];
      d4 = A[i + 4];
      d5 = A[i + 8];
      d6 = A[i + 12];
      for (kidx = 0; kidx < 4; kidx++) {
        coffset = kidx << 2;
        b_A[i + coffset] = ((bkj * tmp[coffset] + d4 * tmp[coffset + 1]) +
                            d5 * tmp[coffset + 2]) +
                           d6 * tmp[coffset + 3];
      }
    }
    std::copy(&b_A[0], &b_A[16], &tmp[0]);
    // 每一次将tmp左乘一次A
    bkj = rows[0];
    d4 = rows[1];
    d5 = rows[2];
    d6 = rows[3];
    for (i = 0; i < 4; i++) {
      ma = i << 2;
      M[(static_cast<int>(bkj) + M.size(0) * i) - 1] = tmp[ma];
      M[(static_cast<int>(d4) + M.size(0) * i) - 1] = tmp[ma + 1];
      M[(static_cast<int>(d5) + M.size(0) * i) - 1] = tmp[ma + 2];
      M[(static_cast<int>(d6) + M.size(0) * i) - 1] = tmp[ma + 3];
    }
    // 将M矩阵写满
  }
  //  定义Q_bar和R_bar
  A_tmp.set_size(j, j);
  loop_ub_tmp = static_cast<int>(N) * static_cast<int>(N);
  for (i = 0; i < loop_ub_tmp; i++) {
    A_tmp[i] = 0;
  }
  if (static_cast<int>(N) > 0) {
    for (int k{0}; k < j; k++) {
      A_tmp[k + A_tmp.size(0) * k] = 1;
    }
  }
  ma = A_tmp.size(0);
  na = A_tmp.size(1);
  i = A_tmp.size(0) << 2;
  Q_bar.set_size(i, i);
  kidx = -1;
  for (coffset = 0; coffset < na; coffset++) {
    for (boffset = 0; boffset < 4; boffset++) {
      for (aoffset = 0; aoffset < ma; aoffset++) {
        i = A_tmp[aoffset + A_tmp.size(0) * coffset];
        j = boffset << 2;
        Q_bar[kidx + 1] = static_cast<double>(i) * Q[j];
        Q_bar[kidx + 2] = static_cast<double>(i) * Q[j + 1];
        Q_bar[kidx + 3] = static_cast<double>(i) * Q[j + 2];
        Q_bar[kidx + 4] = static_cast<double>(i) * Q[j + 3];
        kidx += 4;
      }
    }
  }
  varargin_1.set_size(Q_bar.size(0), Q_bar.size(1));
  na = Q_bar.size(0) * Q_bar.size(1);
  for (i = 0; i < na; i++) {
    varargin_1[i] = Q_bar[i];
  }
  ma = Q_bar.size(0) + 4;
  Q_bar.set_size(ma, ma);
  na = ma * ma;
  for (i = 0; i < na; i++) {
    Q_bar[i] = 0.0;
  }
  if ((varargin_1.size(0) > 0) && (varargin_1.size(1) > 0)) {
    na = varargin_1.size(1);
    ma = varargin_1.size(0);
    for (i = 0; i < na; i++) {
      for (j = 0; j < ma; j++) {
        Q_bar[j + Q_bar.size(0) * i] = varargin_1[j + varargin_1.size(0) * i];
      }
    }
  }
  if (varargin_1.size(0) + 1 > varargin_1.size(0) + 4) {
    i = 0;
    j = -1;
  } else {
    i = varargin_1.size(0);
    j = varargin_1.size(0) + 3;
  }
  if (varargin_1.size(1) + 1 > varargin_1.size(1) + 4) {
    kidx = 0;
    coffset = -1;
  } else {
    kidx = varargin_1.size(1);
    coffset = varargin_1.size(1) + 3;
  }
  na = (j - i) + 1;
  ma = (coffset - kidx) + 1;
  for (j = 0; j < ma; j++) {
    for (coffset = 0; coffset < na; coffset++) {
      Q_bar[(i + coffset) + Q_bar.size(0) * (kidx + j)] = F[coffset + na * j];
    }
  }
  ma = A_tmp.size(0);
  na = A_tmp.size(1);
  R_bar.set_size(A_tmp.size(0), A_tmp.size(1));
  kidx = -1;
  for (coffset = 0; coffset < na; coffset++) {
    for (aoffset = 0; aoffset < ma; aoffset++) {
      R_bar[(kidx + aoffset) + 1] =
          static_cast<double>(A_tmp[aoffset + A_tmp.size(0) * coffset]) * R;
    }
    kidx += ma;
  }
  //  计算G, E, H
  //  G: n x n
  ma = C.size(1);
  na = C.size(0);
  kidx = Q_bar.size(1);
  varargin_1.set_size(C.size(1), Q_bar.size(1));
  for (j = 0; j < kidx; j++) {
    coffset = j * ma;
    boffset = j * Q_bar.size(0);
    for (int b_i{0}; b_i < ma; b_i++) {
      varargin_1[coffset + b_i] = 0.0;
    }
    for (int k{0}; k < na; k++) {
      bkj = Q_bar[boffset + k];
      for (int b_i{0}; b_i < ma; b_i++) {
        i = coffset + b_i;
        varargin_1[i] = varargin_1[i] + C[b_i * C.size(0) + k] * bkj;
      }
    }
  }
  ma = varargin_1.size(0);
  na = varargin_1.size(1);
  E.set_size(varargin_1.size(0), 4);
  for (j = 0; j < 4; j++) {
    coffset = j * ma;
    boffset = j * M.size(0);
    for (int b_i{0}; b_i < ma; b_i++) {
      E[coffset + b_i] = 0.0;
    }
    for (int k{0}; k < na; k++) {
      aoffset = k * varargin_1.size(0);
      bkj = M[boffset + k];
      for (int b_i{0}; b_i < ma; b_i++) {
        i = coffset + b_i;
        E[i] = E[i] + varargin_1[aoffset + b_i] * bkj;
      }
    }
  }
  //  E: NP x n
  ma = varargin_1.size(0);
  na = varargin_1.size(1);
  kidx = C.size(1);
  H.set_size(varargin_1.size(0), C.size(1));
  for (j = 0; j < kidx; j++) {
    coffset = j * ma;
    boffset = j * C.size(0);
    for (int b_i{0}; b_i < ma; b_i++) {
      H[coffset + b_i] = 0.0;
    }
    for (int k{0}; k < na; k++) {
      aoffset = k * varargin_1.size(0);
      bkj = C[boffset + k];
      for (int b_i{0}; b_i < ma; b_i++) {
        i = coffset + b_i;
        H[i] = H[i] + varargin_1[aoffset + b_i] * bkj;
      }
    }
  }
  if ((H.size(0) == R_bar.size(0)) && (H.size(1) == R_bar.size(1))) {
    for (i = 0; i < loop_ub_tmp; i++) {
      H[i] = H[i] + R_bar[i];
    }
  } else {
    plus(H, R_bar);
  }
  //  NP x NP 
}

//
// File trailer for MPC_Matrices.cpp
//
// [EOF]
//
