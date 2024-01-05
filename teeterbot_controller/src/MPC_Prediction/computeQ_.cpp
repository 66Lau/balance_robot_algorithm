//
// File: computeQ_.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 05-Jan-2024 13:02:36
//

// Include Files
#include "computeQ_.h"
#include "MPC_Prediction_internal_types.h"
#include "MPC_Prediction_rtwutil.h"
#include "rt_nonfinite.h"
#include <algorithm>
#include <cstring>

// Function Definitions
//
// Arguments    : e_struct_T &obj
//                int nrows
// Return Type  : void
//
namespace coder {
namespace optim {
namespace coder {
namespace QRManager {
void computeQ_(e_struct_T &obj, int nrows)
{
  double work[11];
  int iQR0;
  int idx;
  int lastc;
  int m;
  int n;
  lastc = obj.minRowCol;
  for (idx = 0; idx < lastc; idx++) {
    iQR0 = 11 * idx + idx;
    n = obj.mrows - idx;
    if (n - 2 >= 0) {
      std::copy(&obj.QR[iQR0 + 1], &obj.QR[iQR0 + ((n + iQR0) - iQR0)],
                &obj.Q[iQR0 + 1]);
    }
  }
  m = obj.mrows;
  if (nrows >= 1) {
    int i;
    int i1;
    int ia;
    int itau;
    i = nrows - 1;
    for (idx = lastc; idx <= i; idx++) {
      ia = idx * 11;
      i1 = m - 1;
      std::memset(&obj.Q[ia], 0,
                  static_cast<unsigned int>(((i1 + ia) - ia) + 1) *
                      sizeof(double));
      obj.Q[ia + idx] = 1.0;
    }
    itau = obj.minRowCol - 1;
    std::memset(&work[0], 0, 11U * sizeof(double));
    for (int b_i{obj.minRowCol}; b_i >= 1; b_i--) {
      int iaii;
      iaii = b_i + (b_i - 1) * 11;
      if (b_i < nrows) {
        int lastv;
        obj.Q[iaii - 1] = 1.0;
        idx = iaii + 11;
        if (obj.tau[itau] != 0.0) {
          boolean_T exitg2;
          lastv = m - b_i;
          iQR0 = (iaii + m) - b_i;
          while ((lastv + 1 > 0) && (obj.Q[iQR0 - 1] == 0.0)) {
            lastv--;
            iQR0--;
          }
          lastc = (nrows - b_i) - 1;
          exitg2 = false;
          while ((!exitg2) && (lastc + 1 > 0)) {
            int exitg1;
            iQR0 = (iaii + lastc * 11) + 11;
            ia = iQR0;
            do {
              exitg1 = 0;
              if (ia <= iQR0 + lastv) {
                if (obj.Q[ia - 1] != 0.0) {
                  exitg1 = 1;
                } else {
                  ia++;
                }
              } else {
                lastc--;
                exitg1 = 2;
              }
            } while (exitg1 == 0);
            if (exitg1 == 1) {
              exitg2 = true;
            }
          }
        } else {
          lastv = -1;
          lastc = -1;
        }
        if (lastv + 1 > 0) {
          double c;
          if (lastc + 1 != 0) {
            if (lastc >= 0) {
              std::memset(&work[0], 0,
                          static_cast<unsigned int>(lastc + 1) *
                              sizeof(double));
            }
            i = (iaii + 11 * lastc) + 11;
            for (n = idx; n <= i; n += 11) {
              c = 0.0;
              i1 = n + lastv;
              for (ia = n; ia <= i1; ia++) {
                c += obj.Q[ia - 1] * obj.Q[((iaii + ia) - n) - 1];
              }
              iQR0 = div_nde_s32_floor((n - iaii) - 11);
              work[iQR0] += c;
            }
          }
          if (!(-obj.tau[itau] == 0.0)) {
            iQR0 = iaii;
            for (idx = 0; idx <= lastc; idx++) {
              c = work[idx];
              if (c != 0.0) {
                c *= -obj.tau[itau];
                i = iQR0 + 11;
                i1 = lastv + iQR0;
                for (n = i; n <= i1 + 11; n++) {
                  obj.Q[n - 1] += obj.Q[((iaii + n) - iQR0) - 12] * c;
                }
              }
              iQR0 += 11;
            }
          }
        }
      }
      if (b_i < m) {
        iQR0 = iaii + 1;
        i = (iaii + m) - b_i;
        for (lastc = iQR0; lastc <= i; lastc++) {
          obj.Q[lastc - 1] *= -obj.tau[itau];
        }
      }
      obj.Q[iaii - 1] = 1.0 - obj.tau[itau];
      for (idx = 0; idx <= b_i - 2; idx++) {
        obj.Q[(iaii - idx) - 2] = 0.0;
      }
      itau--;
    }
  }
}

} // namespace QRManager
} // namespace coder
} // namespace optim
} // namespace coder

//
// File trailer for computeQ_.cpp
//
// [EOF]
//
