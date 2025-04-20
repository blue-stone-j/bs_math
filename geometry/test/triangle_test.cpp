#include <gtest/gtest.h>

#include <iostream>
#include "triangle.h"

TEST(triangle_test, test1)
{
  // Define three points
  Point A = {2, 3};
  Point B = {5, 7};
  Point C = {8, 2};

  // Compute area
  double area = calculateTriangleArea(A, B, C);

  EXPECT_FLOAT_EQ(area, 13.5);
}