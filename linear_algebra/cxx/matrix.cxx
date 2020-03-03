
#include "linear_algebra.h"

#include <stdio.h>
#include <stdlib.h>

matrix::matrix(int m, int n)
{
  data_ = new double[m * n];
  m_ = m;
  n_ = n;
}

matrix::~matrix()
{
  delete[] data_;
}

void matrix::print() const
{
  printf("{\n");
  for (int i = 0; i < n_rows(); i++) {
    printf("{");
    for (int j = 0; j < n_cols(); j++) {
      printf(" %g", (*this)(i, j));
    }
    printf(" }\n");
  }
  printf("}\n");
}
