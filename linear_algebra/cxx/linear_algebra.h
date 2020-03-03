
#ifndef LINEAR_ALGEBRA_H
#define LINEAR_ALGEBRA_H

#include <xtensor/xtensor.hpp>

#include <cassert>
#include <iostream>
#include <vector>

//#define BOUNDS_CHECK

using vector = xt::xtensor<double, 1>;

class matrix
{
public:
  matrix(int m, int n);
  matrix(std::initializer_list<std::initializer_list<double>> l);

  int n_rows() const { return m_; }
  int n_cols() const { return n_; }

  double operator()(int i, int j) const
  {
#ifdef BOUNDS_CHECK
    assert(i >= 0 && i < m_);
    assert(j >= 0 && j < n_);
#endif
    return data_[i * n_ + j];
  }

  double& operator()(int i, int j)
  {
#ifdef BOUNDS_CHECK
    assert(i >= 0 && i < m_);
    assert(j >= 0 && j < n_);
#endif
    return data_[i * n_ + j];
  }

  void print() const;

private:
  std::vector<double> data_;
  int m_, n_;
};

double dot(const vector& x, const vector& y);
vector dot(const matrix& A, const vector& x);

// ----------------------------------------------------------------------

#include <stdio.h>

#define HERE                                                                   \
  fprintf(stderr, "HERE at %s:%d (%s)\n", __FILE__, __LINE__, __FUNCTION__)

#endif
