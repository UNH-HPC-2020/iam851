
#include "linear_algebra.h"

int main(int argc, char** argv)
{
  const int N = 20000;
  double t1b = Wtime();
  vector x = xt::arange(N);
  matrix A = xt::eye(N);
  double t1e = Wtime();
  std::cout << "init took " << t1e - t1b << "\n";

  double t2b = Wtime();
  vector y = dot(A, x);
  double t2e = Wtime();
  std::cout << "dot took " << t2e - t2b << "\n";
}
