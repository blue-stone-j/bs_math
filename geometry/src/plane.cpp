
#include "plane.h"

namespace bmath
{
namespace geometry
{
PointProjection::PointProjection(const Eigen::Vector3d &point_on_plane,
                                 const Eigen::Vector3d &normal_plane) :
  point0(point_on_plane),
  normal(normal_plane)
{
  normal.normalize();

  computePlaneBasis();
}

void PointProjection::setPlane(const Eigen::Vector3d &point_on_plane,
                               const Eigen::Vector3d &normal_plane)
{
  point0 = point_on_plane;
  normal = normal_plane;
  normal.normalize();
  computePlaneBasis();
}

void PointProjection::computePlaneBasis()
{
  u = normal.unitOrthogonal(); // First basis vector
  v = normal.cross(u);         // Second basis vector
}

Eigen::Vector2d PointProjection::projectPointToPlane2D(const Eigen::Vector3d &point)
{
  Eigen::Vector3d relative = point - point0;
  return Eigen::Vector2d(relative.dot(u), relative.dot(v));
}

Eigen::Vector3d PointProjection::map2DTo3D(const double &x, const double y)
{
  return point0 + u * x + v * y;
}

Eigen::Vector3d PointProjection::projectPointOntoPlane(const Eigen::Vector3d &point)
{
  double distance = (point - point0).dot(normal); // Distance from point to plane along normal
  return point - distance * normal;               // Projected point
}

} // namespace geometry
} // namespace bmath