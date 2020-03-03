
#include "linear_algebra.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

vector::vector(int _n)
{
  data = (double*)calloc(_n, sizeof(*data));
  n = _n;
}

vector::~vector()
{
  free(data);
}

void vector::print() const
{
  printf("{");
  for (int i = 0; i < n; i++) {
    printf(" %g", VEC(*this, i));
  }
  printf(" }\n");
}
