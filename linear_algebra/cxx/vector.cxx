
#include "linear_algebra.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

vector::vector(int n)
{
  data_ = new double[n]();
  n_ = n;
}

vector::~vector()
{
  delete[] data_;
}

void vector::print() const
{
  printf("{");
  for (int i = 0; i < n_; i++) {
    printf(" %g", (*this)(i));
  }
  printf(" }\n");
}
