//
// File: countsort.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 05-Jan-2024 13:02:36
//

// Include Files
#include "countsort.h"
#include "rt_nonfinite.h"
#include <cstring>

// Function Definitions
//
// Arguments    : int x[11]
//                int xLen
//                int workspace[11]
//                int xMin
//                int xMax
// Return Type  : void
//
namespace coder {
namespace optim {
namespace coder {
namespace utils {
void countsort(int x[11], int xLen, int workspace[11], int xMin, int xMax)
{
  if ((xLen > 1) && (xMax > xMin)) {
    int idxEnd;
    int idxStart;
    int maxOffset;
    idxStart = xMax - xMin;
    if (idxStart >= 0) {
      std::memset(&workspace[0], 0,
                  static_cast<unsigned int>(idxStart + 1) * sizeof(int));
    }
    maxOffset = idxStart - 1;
    for (int idx{0}; idx < xLen; idx++) {
      idxStart = x[idx] - xMin;
      workspace[idxStart]++;
    }
    for (int idx{2}; idx <= maxOffset + 2; idx++) {
      workspace[idx - 1] += workspace[idx - 2];
    }
    idxStart = 1;
    idxEnd = workspace[0];
    for (int idx{0}; idx <= maxOffset; idx++) {
      for (int idxFill{idxStart}; idxFill <= idxEnd; idxFill++) {
        x[idxFill - 1] = idx + xMin;
      }
      idxStart = workspace[idx] + 1;
      idxEnd = workspace[idx + 1];
    }
    for (int idx{idxStart}; idx <= idxEnd; idx++) {
      x[idx - 1] = xMax;
    }
  }
}

} // namespace utils
} // namespace coder
} // namespace optim
} // namespace coder

//
// File trailer for countsort.cpp
//
// [EOF]
//
