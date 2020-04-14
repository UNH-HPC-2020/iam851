
#include <xtensor/xcsv.hpp>
#include <xtensor/xio.hpp>
#include <xtensor/xpad.hpp>
#include <xtensor/xtensor.hpp>

#include <mpi.h>

#include <cassert>
#include <fstream>
#include <iostream>

class MPIDomain
{
public:
  MPIDomain(MPI_Comm comm, int N) : comm_(comm), N_(N)
  {
    MPI_Comm_rank(comm_, &rank_);
    MPI_Comm_size(comm_, &size_);

    assert(N % size_ == 0); // # grid points must be divisible by # procs
    n_ = N / size_;
  }

  MPI_Comm comm() const { return comm_; }
  int rank() const { return rank_; }
  int size() const { return size_; }

  int N() const { return N_; }
  int n() const { return n_; }

private:
  MPI_Comm comm_;
  int rank_;
  int size_;
  int N_; // global number of grid points
  int n_; // local number of grid points
};

xt::xtensor<double, 1> derivative(const MPIDomain& domain,
                                  const xt::xtensor<double, 1>& f, double dx)
{
  const int G = 1;

  auto f_g = xt::pad(f, G);

  int n = domain.n();
  assert(f.shape(0) == n);

  // fill ghosts
  int left = domain.rank() > 0 ? domain.rank() - 1 : domain.size() - 1;
  int right = domain.rank() < domain.size() - 1 ? domain.rank() + 1 : 0;
  MPI_Send(&f_g(G + 0), 1, MPI_DOUBLE, left, 123, domain.comm());
  MPI_Recv(&f_g(G + n), 1, MPI_DOUBLE, right, 123, domain.comm(),
           MPI_STATUS_IGNORE);

  MPI_Send(&f_g(G + n - 1), 1, MPI_DOUBLE, right, 456, domain.comm());
  MPI_Recv(&f_g(G + -1), 1, MPI_DOUBLE, left, 456, domain.comm(),
           MPI_STATUS_IGNORE);

#if 1
  auto fprime = xt::zeros_like(f);
  for (int i = 0; i < n; i++) {
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

  MPI_Init(&argc, &argv);
  MPIDomain domain(MPI_COMM_WORLD, N);

  // create coordinates [0, 2pi)
  double L = 2. * M_PI; // total size of domain
  double dx = L / N;
  auto x = xt::arange<double>(domain.rank() * domain.n(),
                              (domain.rank() + 1) * domain.n()) *
           dx;

  // our original function f
  auto f = sin(x);

  // calculate derivative
  auto fprime = derivative(domain, f, dx);

  std::ofstream out("f-" + std::to_string(domain.rank()) + ".csv");
  xt::dump_csv(out, xt::stack(xt::xtuple(x, f, fprime), 1));

  MPI_Finalize();
  return 0;
}
