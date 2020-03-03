
#include "linear_algebra.h"

#include <assert.h>

void vector_add(const struct vector& x, const struct vector& y,
                struct vector& z)
{
  assert(x.n == y.n && x.n == z.n);

  for (int i = 0; i < x.n; i++) {
    z(i) = x(i) + y(i);
  }
}
