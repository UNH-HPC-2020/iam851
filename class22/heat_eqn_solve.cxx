
#include "heat_eqn.h"

#include <cassert>
#include <cstdio>
#include <fstream>
#include <iostream>

#include <unistd.h>

template <typename T>
auto sqr(T x)
{
  return x * x;
}

void write_output(const MPIDomain& domain, const xt::xtensor<double, 1>& x,
                  const xt::xtensor<double, 1>& f, int cnt)
{
  std::ofstream out("f" + std::to_string(cnt) + "-" +
                    std::to_string(domain.rank()) + ".csv");
  xt::dump_csv(out, xt::stack(xt::xtuple(x, f), 1));
}

int main(int argc, char** argv)
{
  int N = 100;
  double max_time = 50.;
  int out_every = 10;
  double kappa = .01;

  MPI_Init(&argc, &argv);

  // parse options
  opterr = 0;
  int c;
  while ((c = getopt(argc, argv, "m:N:o:k:")) != -1) {
    switch (c) {
      case 'N': N = atoi(optarg); break;
      case 'm': max_time = atof(optarg); break;
      case 'o': out_every = atoi(optarg); break;
      case 'k': kappa = atof(optarg); break;
      case '?':
        if (optopt == 'N' || optopt == 'm' || optopt == 'o' || optopt == 'k') {
          fprintf(stderr, "Option -%c requires an argument.\n", optopt);
        } else {
          fprintf(stderr, "Unknown option '-%c'.\n", optopt);
        }
        return 1;
      default: abort();
    }
  }

  MPIDomain domain(MPI_COMM_WORLD, N, 2. * M_PI);
  double dt = .5 * sqr(domain.dx()) / kappa; // pick dt to satisfy CFL condition
  int n_timesteps = std::round(max_time / dt);

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == 0) {
    printf("Parameters:\n");
    printf("  -N <N>            number of grid points (%d)\n", N);
    printf("  -m <max_time>     final time to run the simulation to (%g)\n",
           max_time);
    printf("  -o <out_every>    output every so often; 0 for no output (%d)\n",
           out_every);
    printf("  -k <kappa>        heat conductivity (%g)\n", kappa);

    printf("\n");
    printf("Grid spacing dx  = %g\n", domain.dx());
    printf("Timestep     dt  = %g\n", dt);
    printf("CFL number   CFL = %g\n", kappa * dt / sqr(domain.dx()));
    printf("number of steps  = %d\n", n_timesteps);
  }

  // create coordinates
  auto x = domain.coords();

  auto f = xt::eval(exp(-sqr(x - M_PI) / sqr(.5)));

  double t_beg = MPI_Wtime();
  for (int n = 0; n < n_timesteps; n++) {
    // write out current solution every so many steps
    if (out_every > 0 && (n % out_every == 0)) {
      write_output(domain, x, f, n / out_every);
    }

    // A simple forward Euler step x^{n+1} = x^{n} + dt * rhs(x^n)
    // works fine for integrating this equation:

    auto rhs = heat_eqn::calc_rhs(domain, f, kappa);
    f += dt * rhs;
  }
  double t_end = MPI_Wtime();

  if (rank == 0) {
    printf("Integrated %d steps and wrote %d output files. Walltime = %g s\n",
           n_timesteps, out_every > 0 ? n_timesteps / out_every : 0,
           t_end - t_beg);
  }

  MPI_Finalize();
  return 0;
}
