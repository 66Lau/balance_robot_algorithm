//
// File: compute_lambda.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 05-Jan-2024 13:02:36
//

#ifndef COMPUTE_LAMBDA_H
#define COMPUTE_LAMBDA_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
struct struct_T;

struct b_struct_T;

struct e_struct_T;

// Function Declarations
namespace coder {
namespace optim {
namespace coder {
namespace qpactiveset {
void compute_lambda(double workspace[121], struct_T &solution,
                    const b_struct_T &objective, const e_struct_T &qrmanager);

}
} // namespace coder
} // namespace optim
} // namespace coder

#endif
//
// File trailer for compute_lambda.h
//
// [EOF]
//
