
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
    x(i) = 1. + i;
    y(i) = 2. + i;
  }

  EXPECT_EQ(vector_dot(x, y), 20);
}

TEST(LinearAlgebra, VectorAdd)
{
  const int N = 4;
  struct vector x(N);
  struct vector y(N);
  struct vector z(N);

  for (int i = 0; i < N; i++) {
    x(i) = 1. + i;
    y(i) = 2. + i;
  }

  vector_add(x, y, z);
  EXPECT_TRUE(z(0) == 3. && z(1) == 5. && z(2) == 7. && z(3) == 9.);
}

TEST(LinearAlgebra, MatrixVectorMul)
{
  const int N = 3;
  struct vector x(N);
  struct vector y(N);
  struct matrix A(N, N);

  for (int i = 0; i < N; i++) {
    x(i) = 1. + i;
    MAT(A, i, i) = 1. + i;
  }
  MAT(A, 0, 1) = 1.; // make the matrix not purely diagonal

  matrix_vector_mul(A, x, y);
  EXPECT_TRUE(y(0) == 3. && y(1) == 4. && y(2) == 9.);
}


