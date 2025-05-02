
#ifndef PLANE_H
#define PLANE_H

#include "geometry/common.h"

namespace bmath
{
namespace geometry
{
class PointProjection
{
 public:
  PointProjection(const Eigen::Vector3d &point_on_plane = Eigen::Vector3d(0, 0, 0),
                  const Eigen::Vector3d &normal_plane   = Eigen::Vector3d(0, 0, 1));

  void setPlane(const Eigen::Vector3d &point_on_plane, const Eigen::Vector3d &normal_plane);

  // Function to establish an orthonormal basis (u, v) on the plane
  void computePlaneBasis();

  // Function to convert a 3D point to local 2D plane coordinates
  Eigen::Vector2d projectPointToPlane2D(const Eigen::Vector3d &point);

  // Function to convert 2D plane coordinates back to 3D space
  Eigen::Vector3d map2DTo3D(const double &x, const double y);

  Eigen::Vector3d projectPointOntoPlane(const Eigen::Vector3d &point);

 private:
  Eigen::Vector3d point0; // A point on the plane
  Eigen::Vector3d normal; // Normal vector of the plane
  Eigen::Vector3d u, v;
};

} // namespace geometry
} // namespace bmath

#endif // PLANE_H