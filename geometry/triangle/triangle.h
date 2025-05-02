#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "geometry/common.h"

namespace bmath
{
namespace geometry
{
double calculateTriangleArea(const PointXY &A, const PointXY &B, const PointXY &C);
}
} // namespace bmath

#endif