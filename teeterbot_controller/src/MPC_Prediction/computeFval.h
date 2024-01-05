//
// File: computeFval.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 05-Jan-2024 13:02:36
//

#ifndef COMPUTEFVAL_H
#define COMPUTEFVAL_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
struct b_struct_T;

// Function Declarations
namespace coder {
namespace optim {
namespace coder {
namespace qpactiveset {
namespace Objective {
double computeFval(const b_struct_T &obj, double workspace[121],
                   const double H[100], const double f[10], const double x[11]);

}
} // namespace qpactiveset
} // namespace coder
} // namespace optim
} // namespace coder

#endif
//
// File trailer for computeFval.h
//
// [EOF]
//
