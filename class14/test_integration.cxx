
#include "wtime.h"

#include <cmath>
#include <iostream>

double f(double x)
{
  return std::sqrt(1. - x * x);
}

int main(int argc, char** argv)
{
  const int N = 100000000;

  double sum = 0.;
  double dx = 1. / N;

  double t_beg = Wtime();
#pragma omp parallel
  {
    double local_sum = 0.;
#pragma omp for
    for (int i = 0; i < N; i++) {
      local_sum += .5 * dx * (f(i * dx) + f((i + 1) * dx));
    }
    sum += local_sum;
  }
  double t_end = Wtime();
  std::cout << "took " << t_end - t_beg << " sec.\n";

  std::cout << "integral is approximately " << sum << "\n";
}
