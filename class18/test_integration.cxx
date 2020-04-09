
#include <cmath>
#include <iostream>
#include <mpi.h>

double f(double x)
{
  return std::sqrt(1. - x * x);
}

int main(int argc, char** argv)
{
  const int N = 100000000;

  double sum = 0.;
  double dx = 1. / N;

  double t_beg = MPI_Wtime();
#pragma omp parallel for reduction(+ : sum)
  for (int i = 0; i < N; i++) {
    sum += .5 * dx * (f(i * dx) + f((i + 1) * dx));
  }
  double t_end = MPI_Wtime();
  std::cout << "took " << t_end - t_beg << " sec.\n";

  std::cout << "integral is approximately " << sum << "\n";
}
