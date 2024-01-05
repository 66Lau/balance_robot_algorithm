//
// File: iterate.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 05-Jan-2024 13:02:36
//

#ifndef ITERATE_H
#define ITERATE_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
struct struct_T;

struct d_struct_T;

struct f_struct_T;

struct e_struct_T;

struct c_struct_T;

struct b_struct_T;

// Function Declarations
namespace coder {
namespace optim {
namespace coder {
namespace qpactiveset {
void iterate(const double H[100], const double f[10], struct_T &solution,
             d_struct_T &memspace, f_struct_T &workingset,
             e_struct_T &qrmanager, c_struct_T &cholmanager,
             b_struct_T &objective, double options_ObjectiveLimit,
             double options_StepTolerance,
             double runTimeOptions_ProbRelTolFactor,
             boolean_T runTimeOptions_RemainFeasible);

}
} // namespace coder
} // namespace optim
} // namespace coder

#endif
//
// File trailer for iterate.h
//
// [EOF]
//
