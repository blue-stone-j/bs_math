#include "triangle.h"
#include <cmath> // For std::abs

namespace bmath
{
namespace geometry
{
double calculateTriangleArea(const PointXY &A, const PointXY &B, const PointXY &C)
{
  return 0.5 * std::abs(A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y));
}
} // namespace geometry
} // namespace bmath