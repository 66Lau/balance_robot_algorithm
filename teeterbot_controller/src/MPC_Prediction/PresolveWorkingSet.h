//
// File: PresolveWorkingSet.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 05-Jan-2024 13:02:36
//

#ifndef PRESOLVEWORKINGSET_H
#define PRESOLVEWORKINGSET_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
struct struct_T;

struct d_struct_T;

struct f_struct_T;

struct e_struct_T;

// Function Declarations
namespace coder {
namespace optim {
namespace coder {
namespace qpactiveset {
namespace initialize {
void PresolveWorkingSet(struct_T &solution, d_struct_T &memspace,
                        f_struct_T &workingset, e_struct_T &qrmanager);

}
} // namespace qpactiveset
} // namespace coder
} // namespace optim
} // namespace coder

#endif
//
// File trailer for PresolveWorkingSet.h
//
// [EOF]
//
