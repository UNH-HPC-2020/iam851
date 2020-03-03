
#include <gtest/gtest.h>

#include <assert.h>
#include <stdio.h>

#include "linear_algebra.h"

TEST(LinearAlgebra, VectorDot)
{
  vector x = {1., 2., 3.};
  vector y = {2., 3., 4.};

  EXPECT_EQ(dot(x, y), 20);
}

TEST(LinearAlgebra, VectorAdd)
{
  vector x = {1., 2., 3., 4.};
  vector y = {2., 3., 4., 5.};

  EXPECT_EQ(x + y, (vector{3., 5., 7., 9.}));
}

TEST(LinearAlgebra, MatrixVectorMul)
{
  vector x = {1., 2., 3.};
  // clang-format off
  matrix A = {{1., 2., 3.},
	      {3., 4., 5.}};
  // clang-format on

  EXPECT_EQ(dot(A, x), (vector{14., 26.}));
}
