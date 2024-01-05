//
// File: computeFirstOrderOpt.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 05-Jan-2024 13:02:36
//

#ifndef COMPUTEFIRSTORDEROPT_H
#define COMPUTEFIRSTORDEROPT_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
struct struct_T;

struct b_struct_T;

// Function Declarations
namespace coder {
namespace optim {
namespace coder {
namespace qpactiveset {
namespace parseoutput {
void computeFirstOrderOpt(struct_T &solution, const b_struct_T &objective,
                          int workingset_nVar,
                          const double workingset_ATwset[11],
                          int workingset_nActiveConstr, double workspace[121]);

}
} // namespace qpactiveset
} // namespace coder
} // namespace optim
} // namespace coder

#endif
//
// File trailer for computeFirstOrderOpt.h
//
// [EOF]
//
