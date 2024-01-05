//
// File: factorQRE.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 05-Jan-2024 13:02:36
//

// Include Files
#include "factorQRE.h"
#include "MPC_Prediction_internal_types.h"
#include "rt_nonfinite.h"
#include "xnrm2.h"
#include "xzgeqp3.h"
#include "xzlarf.h"
#include "xzlarfg.h"
#include <cmath>
#include <cstring>

// Function Definitions
//
// Arguments    : e_struct_T &obj
//                int mrows
//                int ncols
// Return Type  : void
//
namespace coder {
namespace optim {
namespace coder {
namespace QRManager {
void factorQRE(e_struct_T &obj, int mrows, int ncols)
{
  double vn1[11];
  double vn2[11];
  double work[11];
  double temp;
  if (mrows * ncols == 0) {
    obj.mrows = mrows;
    obj.ncols = ncols;
    obj.minRowCol = 0;
  } else {
    int i;
    obj.usedPivoting = true;
    obj.mrows = mrows;
    obj.ncols = ncols;
    if (mrows <= ncols) {
      i = mrows;
    } else {
      i = ncols;
    }
    obj.minRowCol = i;
    std::memset(&obj.tau[0], 0, 11U * sizeof(double));
    if (i < 1) {
      for (int pvt{0}; pvt < ncols; pvt++) {
        obj.jpvt[pvt] = pvt + 1;
      }
    } else {
      int i1;
      int ix;
      int iy;
      int nfxd;
      int pvt;
      int temp_tmp;
      nfxd = 0;
      for (pvt = 0; pvt < ncols; pvt++) {
        if (obj.jpvt[pvt] != 0) {
          nfxd++;
          if (pvt + 1 != nfxd) {
            ix = pvt * 11;
            iy = (nfxd - 1) * 11;
            for (int k{0}; k < mrows; k++) {
              temp_tmp = ix + k;
              temp = obj.QR[temp_tmp];
              i1 = iy + k;
              obj.QR[temp_tmp] = obj.QR[i1];
              obj.QR[i1] = temp;
            }
            obj.jpvt[pvt] = obj.jpvt[nfxd - 1];
            obj.jpvt[nfxd - 1] = pvt + 1;
          } else {
            obj.jpvt[pvt] = pvt + 1;
          }
        } else {
          obj.jpvt[pvt] = pvt + 1;
        }
      }
      if (nfxd > i) {
        nfxd = i;
      }
      internal::reflapack::qrf(obj.QR, mrows, ncols, nfxd, obj.tau);
      if (nfxd < i) {
        std::memset(&work[0], 0, 11U * sizeof(double));
        std::memset(&vn1[0], 0, 11U * sizeof(double));
        std::memset(&vn2[0], 0, 11U * sizeof(double));
        i1 = nfxd + 1;
        for (pvt = i1; pvt <= ncols; pvt++) {
          temp = internal::blas::xnrm2(mrows - nfxd, obj.QR,
                                       (nfxd + (pvt - 1) * 11) + 1);
          vn1[pvt - 1] = temp;
          vn2[pvt - 1] = temp;
        }
        for (int b_i{i1}; b_i <= i; b_i++) {
          double s;
          int ii;
          int ip1;
          int mmi;
          int nmi;
          ip1 = b_i + 1;
          iy = (b_i - 1) * 11;
          ii = (iy + b_i) - 1;
          nmi = (ncols - b_i) + 1;
          mmi = mrows - b_i;
          if (nmi < 1) {
            nfxd = -2;
          } else {
            nfxd = -1;
            if (nmi > 1) {
              temp = std::abs(vn1[b_i - 1]);
              for (int k{2}; k <= nmi; k++) {
                s = std::abs(vn1[(b_i + k) - 2]);
                if (s > temp) {
                  nfxd = k - 2;
                  temp = s;
                }
              }
            }
          }
          pvt = b_i + nfxd;
          if (pvt + 1 != b_i) {
            ix = pvt * 11;
            for (int k{0}; k < mrows; k++) {
              temp_tmp = ix + k;
              temp = obj.QR[temp_tmp];
              nfxd = iy + k;
              obj.QR[temp_tmp] = obj.QR[nfxd];
              obj.QR[nfxd] = temp;
            }
            nfxd = obj.jpvt[pvt];
            obj.jpvt[pvt] = obj.jpvt[b_i - 1];
            obj.jpvt[b_i - 1] = nfxd;
            vn1[pvt] = vn1[b_i - 1];
            vn2[pvt] = vn2[b_i - 1];
          }
          if (b_i < mrows) {
            temp = obj.QR[ii];
            obj.tau[b_i - 1] =
                internal::reflapack::xzlarfg(mmi + 1, temp, obj.QR, ii + 2);
            obj.QR[ii] = temp;
          } else {
            obj.tau[b_i - 1] = 0.0;
          }
          if (b_i < ncols) {
            temp = obj.QR[ii];
            obj.QR[ii] = 1.0;
            internal::reflapack::xzlarf(mmi + 1, nmi - 1, ii + 1,
                                        obj.tau[b_i - 1], obj.QR, ii + 12,
                                        work);
            obj.QR[ii] = temp;
          }
          for (pvt = ip1; pvt <= ncols; pvt++) {
            nfxd = b_i + (pvt - 1) * 11;
            temp = vn1[pvt - 1];
            if (temp != 0.0) {
              double temp2;
              s = std::abs(obj.QR[nfxd - 1]) / temp;
              s = 1.0 - s * s;
              if (s < 0.0) {
                s = 0.0;
              }
              temp2 = temp / vn2[pvt - 1];
              temp2 = s * (temp2 * temp2);
              if (temp2 <= 1.4901161193847656E-8) {
                if (b_i < mrows) {
                  temp = internal::blas::xnrm2(mmi, obj.QR, nfxd + 1);
                  vn1[pvt - 1] = temp;
                  vn2[pvt - 1] = temp;
                } else {
                  vn1[pvt - 1] = 0.0;
                  vn2[pvt - 1] = 0.0;
                }
              } else {
                vn1[pvt - 1] = temp * std::sqrt(s);
              }
            }
          }
        }
      }
    }
  }
}

} // namespace QRManager
} // namespace coder
} // namespace optim
} // namespace coder

//
// File trailer for factorQRE.cpp
//
// [EOF]
//
