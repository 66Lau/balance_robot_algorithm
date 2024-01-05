//
// File: xgemv.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 05-Jan-2024 13:02:36
//

// Include Files
#include "xgemv.h"
#include "rt_nonfinite.h"
#include <cstring>

// Function Definitions
//
// Arguments    : int m
//                int n
//                const double A[100]
//                int lda
//                const double x[11]
//                double y[10]
// Return Type  : void
//
namespace coder {
namespace internal {
namespace blas {
void xgemv(int m, int n, const double A[100], int lda, const double x[11],
           double y[10])
{
  if ((m != 0) && (n != 0)) {
    int i;
    int ix;
    i = static_cast<unsigned char>(m);
    std::memset(&y[0], 0, static_cast<unsigned int>(i) * sizeof(double));
    ix = 0;
    i = lda * (n - 1) + 1;
    for (int iac{1}; lda < 0 ? iac >= i : iac <= i; iac += lda) {
      int i1;
      i1 = (iac + m) - 1;
      for (int ia{iac}; ia <= i1; ia++) {
        int i2;
        i2 = ia - iac;
        y[i2] += A[ia - 1] * x[ix];
      }
      ix++;
    }
  }
}

} // namespace blas
} // namespace internal
} // namespace coder

//
// File trailer for xgemv.cpp
//
// [EOF]
//
