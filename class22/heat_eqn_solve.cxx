
#include "heat_eqn.h"

#include <cassert>
#include <fstream>
#include <iostream>

template <typename T>
auto sqr(T x)
{
  return x * x;
}

int main(int argc, char** argv)
{
  const int N = 100;
  const int n_timesteps = 200;
  const int out_every = 10;
  const double kappa = .01;

  MPI_Init(&argc, &argv);
  MPIDomain domain(MPI_COMM_WORLD, N, 2. * M_PI);

  double dx = 2. * M_PI / N;
  double dt = .5 * sqr(dx) / kappa; // pick dt to satisfy CFL condition

  auto x = xt::arange<double>(0, N) * dx;
  auto f = xt::eval(exp(-sqr(x - M_PI) / sqr(.5)));

  for (int n = 0; n < n_timesteps; n++) {
    // write out current solution every so many steps
    if (n % out_every == 0) {
      std::ofstream out("f" + std::to_string(n) + ".csv");
      xt::dump_csv(out, xt::stack(xt::xtuple(x, f), 1));
    }

    // A simple forward Euler step x^{n+1} = x^{n} + dt * rhs(x^n)
    // works fine for integrating this equation:

    auto rhs = heat_eqn::calc_rhs(domain, f, kappa);
    f += dt * rhs;
  }

  MPI_Finalize();
  return 0;
}
