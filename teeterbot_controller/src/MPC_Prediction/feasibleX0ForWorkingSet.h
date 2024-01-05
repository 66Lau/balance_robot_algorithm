//
// File: feasibleX0ForWorkingSet.h
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 05-Jan-2024 13:02:36
//

#ifndef FEASIBLEX0FORWORKINGSET_H
#define FEASIBLEX0FORWORKINGSET_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Declarations
struct f_struct_T;

struct e_struct_T;

// Function Declarations
namespace coder {
namespace optim {
namespace coder {
namespace qpactiveset {
namespace initialize {
boolean_T feasibleX0ForWorkingSet(double workspace[121], double xCurrent[11],
                                  const f_struct_T &workingset,
                                  e_struct_T &qrmanager);

}
} // namespace qpactiveset
} // namespace coder
} // namespace optim
} // namespace coder

#endif
//
// File trailer for feasibleX0ForWorkingSet.h
//
// [EOF]
//
