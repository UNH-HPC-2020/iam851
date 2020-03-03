
#include <gtest/gtest.h>

#include <assert.h>
#include <stdio.h>

#include "linear_algebra.h"

TEST(LinearAlgebra, VectorDot)
{
  vector x = { 1., 2., 3. };
  vector y = { 2., 3., 4. };

  EXPECT_EQ(dot(x, y), 20);
}

TEST(LinearAlgebra, VectorAdd)
{
  vector x = { 1., 2., 3., 4. };
  vector y = { 2., 3., 4., 5. };

  EXPECT_EQ(x + y, (vector{3., 5., 7., 9.}));
}

TEST(LinearAlgebra, MatrixVectorMul)
{
  const int N = 3;
  vector x = { 1., 2., 3. };
  matrix A(N, N);

  for (int i = 0; i < N; i++) {
    A(i, i) = 1. + i;
  }
  A(0, 1) = 1.; // make the matrix not purely diagonal

  EXPECT_EQ(A * x, (vector{3., 4., 9.}));
}
