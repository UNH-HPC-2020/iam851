
#include "linear_algebra.h"

#include <stdio.h>
#include <stdlib.h>

matrix::matrix(int m, int n) : data_(m * n), m_(m), n_(n) {}

matrix::matrix(std::initializer_list<std::initializer_list<double>> l)
{
  m_ = l.size();
  n_ = l.begin()->size();
  data_.resize(m_ * n_);

  int i = 0;
  for (auto& row : l) {
    int j = 0;
    for (auto& val : row) {
      (*this)(i, j) = val;
      j++;
    }
    i++;
  }
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
