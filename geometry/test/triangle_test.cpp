#include <gtest/gtest.h>

#include <iostream>
#include "geometry/triangle/triangle.h"

TEST(triangle_test, test1)
{
  // Define three points
  bmath::geometry::PointXY A = {2, 3};
  bmath::geometry::PointXY B = {5, 7};
  bmath::geometry::PointXY C = {8, 2};

  // Compute area
  double area = bmath::geometry::calculateTriangleArea(A, B, C);

  EXPECT_FLOAT_EQ(area, 13.5);
}