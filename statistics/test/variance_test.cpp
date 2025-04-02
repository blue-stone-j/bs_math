#include <gtest/gtest.h>

#include "variance.h"

TEST(variance_test, test1)
{
  Eigen::VectorXf vector(5);
  vector << 1, 2, 3, 4, 5;
  float variance = math::statistics::computeVariance(vector);
  EXPECT_FLOAT_EQ(variance, 2.0);
  // The variance of the vector [1, 2, 3, 4, 5] is 2.0
  // because the mean is 3.0 and the squared differences are
  // [4, 1, 0, 1, 4], which sum to 10. Dividing by the number of
  // elements (5) gives us 2.0.
}