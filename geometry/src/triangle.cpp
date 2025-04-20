#include "triangle.h"
#include <cmath> // For std::abs


double calculateTriangleArea(const Point &A, const Point &B, const Point &C)
{
  return 0.5 * std::abs(A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y));
}
