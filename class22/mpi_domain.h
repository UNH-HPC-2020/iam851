
#ifndef MPI_DOMAIN_H
#define MPI_DOMAIN_H

#include <xtensor/xtensor.hpp>

#include <mpi.h>

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

  void fill_ghosts(xt::xtensor<double, 1>& f_g) const
  {
    const int G = 1; // assumes one ghost point
    assert(f_g.shape(0) == n_ + 2 * G);

    MPI_Request reqs[4];
    MPI_Irecv(&f_g(G + n_), 1, MPI_DOUBLE, rank_right(), 123, comm(), &reqs[0]);
    MPI_Irecv(&f_g(G + -1), 1, MPI_DOUBLE, rank_left(), 456, comm(), &reqs[1]);
    MPI_Isend(&f_g(G + 0), 1, MPI_DOUBLE, rank_left(), 123, comm(), &reqs[2]);
    MPI_Isend(&f_g(G + n_ - 1), 1, MPI_DOUBLE, rank_right(), 456, comm(),
              &reqs[3]);
    MPI_Waitall(4, reqs, MPI_STATUSES_IGNORE);
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

#endif
