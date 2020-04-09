
#include <cassert>
#include <cmath>
#include <iostream>
#include <mpi.h>

double f(double x)
{
  return std::sqrt(1. - x * x);
}

int main(int argc, char** argv)
{
  const int N = 100;

  MPI_Init(&argc, &argv);

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  assert(size == 2); // needs to be run on exactly two procs for now

  double sum = 0.;
  double dx = 1. / N;
  int ib, ie;
  if (rank == 0) {
    ib = 0;
    ie = 50;
  } else if (rank == 1) {
    ib = 50;
    ie = 100;
  }

  double t_beg = MPI_Wtime();
  for (int i = ib; i < ie; i++) {
    sum += .5 * dx * (f(i * dx) + f((i + 1) * dx));
  }
  double t_end = MPI_Wtime();
  std::cout << "took " << t_end - t_beg << " sec.\n";

  std::cout << "integral is approximately " << sum << "\n";

  MPI_Finalize();
  return 0;
}
