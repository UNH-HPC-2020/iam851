
#include "linear_algebra.h"

#include <stdio.h>
#include <stdlib.h>

matrix::matrix(int _m, int _n)
{
  data = (double*)calloc(_m * _n, sizeof(*data));
  m = _m;
  n = _n;
}

void matrix_destruct(struct matrix& A)
{
  free(A.data);
}

void matrix::print() const
{
  printf("{\n");
  for (int i = 0; i < m; i++) {
    printf("{");
    for (int j = 0; j < n; j++) {
      printf(" %g", MAT(*this, i, j));
    }
    printf(" }\n");
  }
  printf("}\n");
}
