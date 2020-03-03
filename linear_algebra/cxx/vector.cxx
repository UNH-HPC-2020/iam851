
#include "linear_algebra.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

vector::vector(int n) : data_(n) {}

vector::vector(std::initializer_list<double> l) : data_(l) {}

std::ostream& operator<<(std::ostream& of, const vector& v)
{
  of << "{";
  for (int i = 0; i < v.size(); i++) {
    of << " " << v(i);
  }
  of << " }";
  return of;
}
