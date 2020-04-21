
#ifndef HEAT_EQN_H
#define HEAT_EQN_H

#include "mpi_domain.h"

#include <xtensor/xcsv.hpp>
#include <xtensor/xio.hpp>
#include <xtensor/xpad.hpp>
#include <xtensor/xtensor.hpp>

#include <mpi.h>

namespace heat_eqn
{

// ----------------------------------------------------------------------
// calculate the r.h.s of the heat equation
//
// u_t = kappa u_xx

inline xt::xtensor<double, 1> calc_rhs(const MPIDomain& domain,
                                       const xt::xtensor<double, 1>& f,
                                       double kappa)
{
  const int G = 1;

  auto f_g = xt::pad(f, G);
  int N = f.size();
  f_g(G - 1) = f_g(G + N - 1);
  f_g(G + N) = f_g(G + 0);

  // Python equivalent: return kappa * (f_g[2:] - 2 * f_g[1;-1] + f_g[:-2]) /
  // (dx^2);
  double dx = domain.dx();
  return kappa *
         (xt::view(f_g, xt::range(2, _)) -
          2. * xt::view(f_g, xt::range(1, -1)) +
          xt::view(f_g, xt::range(_, -2))) /
         (dx * dx);
}

} // namespace heat_eqn

#endif
