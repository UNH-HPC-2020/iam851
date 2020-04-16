
#ifndef HEAT_EQN_H
#define HEAT_EQN_H

#include <xtensor/xcsv.hpp>
#include <xtensor/xio.hpp>
#include <xtensor/xpad.hpp>
#include <xtensor/xtensor.hpp>

#include <mpi.h>

namespace heat_eqn
{

inline xt::xtensor<double, 1> calc_rhs(const xt::xtensor<double, 1>& f, double dx)
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

#endif
