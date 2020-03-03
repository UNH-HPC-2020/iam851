
#include "linear_algebra.h"

#include <stdio.h>
#include <stdlib.h>

matrix::matrix(int _m, int _n)
{
  data = new double[_m * _n];
  m = _m;
  n = _n;
}

matrix::~matrix()
{
  delete[] data;
}

void matrix::print() const
{
  printf("{\n");
  for (int i = 0; i < m; i++) {
    printf("{");
    for (int j = 0; j < n; j++) {
      printf(" %g", (*this)(i, j));
    }
    printf(" }\n");
  }
  printf("}\n");
}
