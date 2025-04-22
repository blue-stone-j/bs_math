
#include "plane.h"

namespace bmath
{
namespace geometry
{
Eigen::Vector3d projectPointOntoPlane(
    const Eigen::Vector3d &p,  // The point to project
    const Eigen::Vector3d &p0, // A point on the plane
    const Eigen::Vector3d &n)  // The normal vector of the plane
{
  Eigen::Vector3d n_unit = n.normalized();       // Ensure normal vector is unit length
  double d               = (p - p0).dot(n_unit); // Distance from point to plane along normal
  return p - d * n_unit;                         // Projected point
}
} // namespace geometry
} // namespace bmath