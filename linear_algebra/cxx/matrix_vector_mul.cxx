
#include "linear_algebra.h"

#include <cassert>

vector dot(const matrix& A, const vector& x)
{
  assert(A.shape(1) == x.size());

  auto y = xt::empty<double>({A.shape(0)});

  for (int i = 0; i < y.size(); i++) {
    y(i) = 0.;
    for (int j = 0; j < x.size(); j++) {
      y(i) += A(i, j) * x(j);
    }
  }

  return y;
}
