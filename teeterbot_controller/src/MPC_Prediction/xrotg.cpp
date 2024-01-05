//
// File: xrotg.cpp
//
// MATLAB Coder version            : 5.6
// C/C++ source code generated on  : 05-Jan-2024 13:02:36
//

// Include Files
#include "xrotg.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions
//
// Arguments    : double &a
//                double &b
//                double &s
// Return Type  : double
//
namespace coder {
namespace internal {
namespace blas {
double xrotg(double &a, double &b, double &s)
{
  double absa;
  double absb;
  double c;
  double roe;
  double scale;
  roe = b;
  absa = std::abs(a);
  absb = std::abs(b);
  if (absa > absb) {
    roe = a;
  }
  scale = absa + absb;
  if (scale == 0.0) {
    s = 0.0;
    c = 1.0;
    a = 0.0;
    b = 0.0;
  } else {
    double ads;
    double bds;
    ads = absa / scale;
    bds = absb / scale;
    scale *= std::sqrt(ads * ads + bds * bds);
    if (roe < 0.0) {
      scale = -scale;
    }
    c = a / scale;
    s = b / scale;
    if (absa > absb) {
      b = s;
    } else if (c != 0.0) {
      b = 1.0 / c;
    } else {
      b = 1.0;
    }
    a = scale;
  }
  return c;
}

} // namespace blas
} // namespace internal
} // namespace coder

//
// File trailer for xrotg.cpp
//
// [EOF]
//
