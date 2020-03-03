
#include "linear_algebra.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

vector::vector(int _n)
{
  data = new double[_n]();
  n = _n;
}

vector::~vector()
{
  delete[] data;
}

void vector::print() const
{
  printf("{");
  for (int i = 0; i < n; i++) {
    printf(" %g", (*this)(i));
  }
  printf(" }\n");
}
