#include <gtest/gtest.h>

#include "statistics/variance/variance.h"

TEST(variance_test, variance)
{
  Eigen::VectorXf vector(5);
  vector << 1, 2, 3, 4, 5;
  float variance = math::statistics::computeVariance(vector);
  EXPECT_FLOAT_EQ(variance, 2.0);
}

TEST(variance_test, covariance)
{
  std::vector<double> X = {1.0, 2.0, 3.0, 4.0, 5.0};
  std::vector<double> Y = {2.1, 2.9, 3.2, 4.8, 5.6};

  try
  {
    double covariance = math::statistics::computeCovariance(X, Y);
    EXPECT_FLOAT_EQ(covariance, 1.78);
  }
  catch (const std::exception &e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
  }
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
