
#include "linear_algebra.h"

#include <stdio.h>
#include <stdlib.h>

vector::vector(int _n)
{
  data = (double*)calloc(_n, sizeof(*data));
  n = _n;
}

void vector_destruct(struct vector& v)
{
  free(v.data);
}

void vector::print() const
{
  printf("{");
  for (int i = 0; i < n; i++) {
    printf(" %g", VEC(*this, i));
  }
  printf(" }\n");
}
