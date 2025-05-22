
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "geometry/common.h"

namespace bmath
{
namespace geometry
{
// Normalize vector
Eigen::Vector3d normalize(const Eigen::Vector3d &v);

// Compute rotation matrix Rx(roll) * Ry(pitch)
Eigen::Matrix3d rotationMatrix(double pitch, double roll);

// Compute cost function: squared error
double costFunction(const Eigen::Vector3d &v1, const Eigen::Vector3d &v2, double pitch, double roll);
} // namespace geometry
} // namespace bmath

#endif // TRANSFORM_H