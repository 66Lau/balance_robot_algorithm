//
// File: xgemv.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 05-Jan-2024 13:02:36
//

#ifndef XGEMV_H
#define XGEMV_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
namespace blas {
void xgemv(int m, int n, const double A[100], int lda, const double x[11],
           double y[10]);

}
} // namespace internal
} // namespace coder

#endif
//
// File trailer for xgemv.h
//
// [EOF]
//
