
#ifndef LINEAR_ALGEBRA_H
#define LINEAR_ALGEBRA_H

#include <cassert>
#include <iostream>
#include <vector>

//#define BOUNDS_CHECK

class vector
{
public:
  vector(int n);

  int size() const { return data_.size(); }

  double operator()(int i) const
  {
#ifdef BOUNDS_CHECK
    assert(i >= 0 && i < size());
#endif
    return data_[i];
  }

  double& operator()(int i)
  {
#ifdef BOUNDS_CHECK
    assert(i >= 0 && i < size());
#endif
    return data_[i];
  }

private:
  std::vector<double> data_;
};

std::ostream& operator<<(std::ostream& of, const vector& v);

class matrix
{
public:
  matrix(int m, int n);

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

double vector_dot(const vector& x, const vector& y);
void vector_add(const vector& x, const vector& y, vector& z);
void matrix_vector_mul(const matrix& A, const vector& x, vector& y);

// ----------------------------------------------------------------------

#include <stdio.h>

#define HERE                                                                   \
  fprintf(stderr, "HERE at %s:%d (%s)\n", __FILE__, __LINE__, __FUNCTION__)

#endif
