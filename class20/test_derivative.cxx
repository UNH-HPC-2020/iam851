
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
  MPIDomain(MPI_Comm comm, int N, double L) : comm_(comm), N_(N), L_(L)
  {
    MPI_Comm_rank(comm_, &rank_);
    MPI_Comm_size(comm_, &size_);

    assert(N % size_ == 0); // # grid points must be divisible by # procs
    n_ = N / size_;
    dx_ = L / N_;
  }

  MPI_Comm comm() const { return comm_; }
  int rank() const { return rank_; }
  int size() const { return size_; }
  int rank_left() const { return rank_ > 0 ? rank_ - 1 : size_ - 1; }
  int rank_right() const { return rank_ < size_ - 1 ? rank_ + 1 : 0; }

  int N() const { return N_; }
  int n() const { return n_; }
  double dx() const { return dx_; }

  int local_begin() const { return rank_ * n_; }
  int local_end() const { return (rank_ + 1) * n_; }

  auto coords() const
  {
    return xt::arange<double>(local_begin(), local_end()) * dx();
  }

private:
  MPI_Comm comm_;
  int rank_;
  int size_;
  int N_;     // global number of grid points
  int n_;     // local number of grid points
  double L_;  // global domain length
  double dx_; // grid spacing
};

xt::xtensor<double, 1> derivative(const MPIDomain& domain,
                                  const xt::xtensor<double, 1>& f)
{
  const int G = 1;

  auto f_g = xt::pad(f, G);

  int n = domain.n();
  double dx = domain.dx();
  assert(f.shape(0) == n);

  // fill ghosts
  MPI_Send(&f_g(G + 0), 1, MPI_DOUBLE, domain.rank_left(), 123, domain.comm());
  MPI_Recv(&f_g(G + n), 1, MPI_DOUBLE, domain.rank_right(), 123, domain.comm(),
           MPI_STATUS_IGNORE);

  MPI_Send(&f_g(G + n - 1), 1, MPI_DOUBLE, domain.rank_right(), 456,
           domain.comm());
  MPI_Recv(&f_g(G + -1), 1, MPI_DOUBLE, domain.rank_left(), 456, domain.comm(),
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
  MPIDomain domain(MPI_COMM_WORLD, N, 2. * M_PI);

  // create coordinates
  auto x = domain.coords();

  // our original function f
  auto f = sin(x);

  // calculate derivative
  auto fprime = derivative(domain, f);

  std::ofstream out("f-" + std::to_string(domain.rank()) + ".csv");
  xt::dump_csv(out, xt::stack(xt::xtuple(x, f, fprime), 1));

  MPI_Finalize();
  return 0;
}
