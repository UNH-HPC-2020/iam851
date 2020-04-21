
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
  double kappa = .7;

  auto x = xt::arange<double>(0, N) * dx;
  auto f = cos(x);
  auto ref = -kappa * cos(x);

  auto rhs = heat_eqn::calc_rhs(f, dx, kappa);

  std::ofstream out("f.csv");
  xt::dump_csv(out, xt::stack(xt::xtuple(x, f, rhs, ref), 1));

  auto max_difference = xt::amax(abs(rhs - ref));
  assert(max_difference() < 1e-3);

  MPI_Finalize();
  return 0;
}
