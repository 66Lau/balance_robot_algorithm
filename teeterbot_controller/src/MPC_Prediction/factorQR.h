//
// File: factorQR.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 05-Jan-2024 13:02:36
//

#ifndef FACTORQR_H
#define FACTORQR_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
struct e_struct_T;

// Function Declarations
namespace coder {
namespace optim {
namespace coder {
namespace QRManager {
void factorQR(e_struct_T &obj, const double A[11], int mrows, int ncols);

}
} // namespace coder
} // namespace optim
} // namespace coder

#endif
//
// File trailer for factorQR.h
//
// [EOF]
//
