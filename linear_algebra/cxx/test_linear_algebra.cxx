
#include <gtest/gtest.h>

#include <assert.h>
#include <stdio.h>

#include "linear_algebra.h"

TEST(LinearAlgebra, VectorDot)
{
  const int N = 3;
  struct vector x(N);
  struct vector y(N);

  for (int i = 0; i < N; i++) {
    VEC(x, i) = 1. + i;
    VEC(y, i) = 2. + i;
  }

  EXPECT_EQ(vector_dot(x, y), 20);

  vector_destruct(x);
  vector_destruct(y);
}

TEST(LinearAlgebra, VectorAdd)
{
  const int N = 4;
  struct vector x(N);
  struct vector y(N);
  struct vector z(N);

  for (int i = 0; i < N; i++) {
    VEC(x, i) = 1. + i;
    VEC(y, i) = 2. + i;
  }

  vector_add(x, y, z);
  EXPECT_TRUE(VEC(z, 0) == 3. && VEC(z, 1) == 5. && VEC(z, 2) == 7. &&
              VEC(z, 3) == 9.);

  vector_destruct(x);
  vector_destruct(y);
  vector_destruct(z);
}

TEST(LinearAlgebra, MatrixVectorMul)
{
  const int N = 3;
  struct vector x(N);
  struct vector y(N);
  struct matrix A(N, N);

  for (int i = 0; i < N; i++) {
    VEC(x, i) = 1. + i;
    MAT(A, i, i) = 1. + i;
  }
  MAT(A, 0, 1) = 1.; // make the matrix not purely diagonal

  matrix_vector_mul(A, x, y);
  EXPECT_TRUE(VEC(y, 0) == 3. && VEC(y, 1) == 4. && VEC(y, 2) == 9.);

  vector_destruct(x);
  vector_destruct(y);
  matrix_destruct(A);
}
