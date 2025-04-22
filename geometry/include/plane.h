
#ifndef PLANE_H
#define PLANE_H

#include "common.h"

namespace bmath
{
namespace geometry
{
Eigen::Vector3d projectPointOntoPlane(
    const Eigen::Vector3d &p,  // The point to project
    const Eigen::Vector3d &p0, // A point on the plane
    const Eigen::Vector3d &n); // The normal vector of the plane
} // namespace geometry
} // namespace bmath

#endif // PLANE_H