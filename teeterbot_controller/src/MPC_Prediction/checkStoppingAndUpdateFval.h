//
// File: checkStoppingAndUpdateFval.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 05-Jan-2024 13:02:36
//

#ifndef CHECKSTOPPINGANDUPDATEFVAL_H
#define CHECKSTOPPINGANDUPDATEFVAL_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
struct struct_T;

struct d_struct_T;

struct b_struct_T;

struct f_struct_T;

struct e_struct_T;

// Function Declarations
namespace coder {
namespace optim {
namespace coder {
namespace qpactiveset {
namespace stopping {
void checkStoppingAndUpdateFval(int &activeSetChangeID, const double f[10],
                                struct_T &solution, d_struct_T &memspace,
                                const b_struct_T &objective,
                                const f_struct_T &workingset,
                                e_struct_T &qrmanager,
                                double options_ObjectiveLimit,
                                boolean_T updateFval);

}
} // namespace qpactiveset
} // namespace coder
} // namespace optim
} // namespace coder

#endif
//
// File trailer for checkStoppingAndUpdateFval.h
//
// [EOF]
//
