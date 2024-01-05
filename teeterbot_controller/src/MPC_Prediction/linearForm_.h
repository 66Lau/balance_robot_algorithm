//
// File: linearForm_.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 05-Jan-2024 13:02:36
//

#ifndef LINEARFORM__H
#define LINEARFORM__H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace optim {
namespace coder {
namespace qpactiveset {
namespace Objective {
void linearForm_(boolean_T obj_hasLinear, int obj_nvar, double workspace[121],
                 const double H[100], const double f[10], const double x[11]);

}
} // namespace qpactiveset
} // namespace coder
} // namespace optim
} // namespace coder

#endif
//
// File trailer for linearForm_.h
//
// [EOF]
//
