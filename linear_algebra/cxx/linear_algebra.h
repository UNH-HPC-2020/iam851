
#ifndef LINEAR_ALGEBRA_H
#define LINEAR_ALGEBRA_H

#include <assert.h>

//#define BOUNDS_CHECK

struct vector
{
  double* data;
  int n;

  vector(int n);
  ~vector();

  double at(int i) const
  {
#ifdef BOUNDS_CHECK
    assert(i >= 0 && i < n);
#endif
    return data[i];
  }

  double& at(int i)
  {
#ifdef BOUNDS_CHECK
    assert(i >= 0 && i < n);
#endif
    return data[i];
  }

  void print() const;
};

#ifdef BOUNDS_CHECK
#define VEC(v, i)                                                              \
  (*({                                                                         \
    assert(i >= 0 && i < (v).n);                                               \
    &(v).data[i];                                                              \
  }))
#else
#define VEC(v, i) ((v).data[i])
#endif

struct matrix
{
  double* data;
  int m, n;

  matrix(int m, int n);
  ~matrix();

  void print() const;
};

#ifdef BOUNDS_CHECK
#define MAT(A, i, j)                                                           \
  (*({                                                                         \
    assert(i >= 0 && i < (A).m);                                               \
    assert(j >= 0 && j < (A).n);                                               \
    &(A).data[i * (A).n + j];                                                  \
  }))
#else
#define MAT(A, i, j) ((A).data[i * (A).n + j])
#endif

double vector_dot(const struct vector& x, const struct vector& y);
void vector_add(const struct vector& x, const struct vector& y,
                const struct vector& z);
void matrix_vector_mul(const struct matrix& A, const struct vector& x,
                       struct vector& y);

// ----------------------------------------------------------------------

#include <stdio.h>

#define HERE                                                                   \
  fprintf(stderr, "HERE at %s:%d (%s)\n", __FILE__, __LINE__, __FUNCTION__)

#endif
