
#include "heat_eqn.h"

#include <cassert>
#include <fstream>
#include <iostream>

// ----------------------------------------------------------------------
// main
//
// tests that the r.h.s (2nd derivative) for a cosine is -cosine.

int main(int argc, char** argv)
{
  MPI_Init(&argc, &argv);

  const int N = 100;
  double dx = 2. * M_PI / N;

  auto x = xt::arange<double>(0, N) * dx;
  auto f = cos(x);
  auto ref = -cos(x);

  auto rhs = heat_eqn::calc_rhs(f, dx);

  std::ofstream out("f.csv");
  xt::dump_csv(out, xt::stack(xt::xtuple(x, f, rhs, ref), 1));

  // TODO: add an automated check that checks that the calculated r.h.s. indeed
  // matches (up to some tolerance the reference result -cos(x)

  MPI_Finalize();
  return 0;
}
