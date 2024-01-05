//
// File: compute_deltax.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 05-Jan-2024 13:02:36
//

#ifndef COMPUTE_DELTAX_H
#define COMPUTE_DELTAX_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
struct struct_T;

struct d_struct_T;

struct e_struct_T;

struct c_struct_T;

struct b_struct_T;

// Function Declarations
namespace coder {
namespace optim {
namespace coder {
namespace qpactiveset {
void compute_deltax(const double H[100], struct_T &solution,
                    d_struct_T &memspace, const e_struct_T &qrmanager,
                    c_struct_T &cholmanager, const b_struct_T &objective);

}
} // namespace coder
} // namespace optim
} // namespace coder

#endif
//
// File trailer for compute_deltax.h
//
// [EOF]
//
