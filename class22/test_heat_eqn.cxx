
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
  const int N = 100;
  double kappa = .7;

  MPI_Init(&argc, &argv);
  MPIDomain domain(MPI_COMM_WORLD, N, 2. * M_PI);

  // create coordinates
  auto x = domain.coords();

  double dx = 2. * M_PI / N;

  auto f = cos(x);
  auto ref = -kappa * cos(x);

  auto rhs = heat_eqn::calc_rhs(domain, f, kappa);

  std::ofstream out("f-" + std::to_string(domain.rank()) + ".csv");
  xt::dump_csv(out, xt::stack(xt::xtuple(x, f, rhs, ref), 1));

  auto max_difference = xt::amax(abs(rhs - ref));
  assert(max_difference() < 1e-3);

  MPI_Finalize();
  return 0;
}
