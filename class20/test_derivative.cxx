
#include <xtensor/xcsv.hpp>
#include <xtensor/xio.hpp>
#include <xtensor/xpad.hpp>
#include <xtensor/xtensor.hpp>

#include <fstream>
#include <iostream>

xt::xtensor<double, 1> derivative(const xt::xtensor<double, 1>& f, double dx)
{
  const int G = 1;

  int N = f.shape(0);
  auto f_g = xt::pad(f, G);
  f_g(G + -1) = f_g(G + N - 1);
  f_g(G + N) = f_g(G + 0);

#if 1
  auto fprime = xt::zeros_like(f);
  for (int i = 0; i < N; i++) {
    fprime(i) = (f_g(i + G + 1) - f_g(i + G - 1)) / (2. * dx);
  }

  return fprime;
#else
  // Python equivalent: return (f_g[2:] - f_g[:-2]) / (2. * dx);
  return (xt::view(f_g, xt::range(2, _)) - xt::view(f_g, xt::range(_, -2))) /
         (2. * dx);
#endif
}

int main(int argc, char** argv)
{
  const int N = 16; // number of grid points

  // create coordinates [0, 2pi)
  double dx = 2. * M_PI / N;
  auto x = xt::arange<double>(0., 2. * M_PI, dx);

  // our original function f
  auto f = sin(x);

  // calculate derivative
  auto fprime = derivative(f, dx);

  std::ofstream out("f.csv");
  xt::dump_csv(out, xt::stack(xt::xtuple(x, f, fprime), 1));

  return 0;
}
