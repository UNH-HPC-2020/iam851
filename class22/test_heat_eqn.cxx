
#include <xtensor/xcsv.hpp>
#include <xtensor/xio.hpp>
#include <xtensor/xpad.hpp>
#include <xtensor/xtensor.hpp>

#include <mpi.h>

#include <cassert>
#include <fstream>
#include <iostream>

namespace heat_eqn
{

xt::xtensor<double, 1> calc_rhs(const xt::xtensor<double, 1>& f, double dx)
{
  const int G = 1;

  auto f_g = xt::pad(f, G);
  // TODO: fill ghost points assuming periodic b.c.

  // Python equivalent: return (f_g[2:] - 2 * f_g[1;-1] + f_g[:-2]) / (dx^2);
  return (xt::view(f_g, xt::range(2, _)) -
          2. * xt::view(f_g, xt::range(1, -1)) +
          xt::view(f_g, xt::range(_, -2))) /
         (dx * dx);
}

} // namespace heat_eqn

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
