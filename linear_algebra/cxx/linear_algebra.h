
#ifndef LINEAR_ALGEBRA_H
#define LINEAR_ALGEBRA_H

#include <assert.h>

//#define BOUNDS_CHECK

class vector
{
public:
  vector(int n);
  ~vector();

  int size() const { return n_; }

  double operator()(int i) const
  {
#ifdef BOUNDS_CHECK
    assert(i >= 0 && i < n_);
#endif
    return data_[i];
  }

  double& operator()(int i)
  {
#ifdef BOUNDS_CHECK
    assert(i >= 0 && i < n_);
#endif
    return data_[i];
  }

  void print() const;

private:
  double* data_;
  int n_;
};

struct matrix
{
  double* data;
  int m, n;

  matrix(int m, int n);
  ~matrix();

  double operator()(int i, int j) const
  {
#ifdef BOUNDS_CHECK
    assert(i >= 0 && i < m);
    assert(j >= 0 && j < n);
#endif
    return data[i * n + j];
  }

  double& operator()(int i, int j)
  {
#ifdef BOUNDS_CHECK
    assert(i >= 0 && i < m);
    assert(j >= 0 && j < n);
#endif
    return data[i * n + j];
  }

  void print() const;
};

double vector_dot(const vector& x, const vector& y);
void vector_add(const vector& x, const vector& y, vector& z);
void matrix_vector_mul(const matrix& A, const vector& x, vector& y);

// ----------------------------------------------------------------------

#include <stdio.h>

#define HERE                                                                   \
  fprintf(stderr, "HERE at %s:%d (%s)\n", __FILE__, __LINE__, __FUNCTION__)

#endif
