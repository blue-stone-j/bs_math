
#include "transform.h"

namespace bmath
{
namespace geometry
{
// Normalize vector
Eigen::Vector3d normalize(const Eigen::Vector3d &v)
{
  return v / v.norm();
}

Eigen::Matrix3d eulerToRotationMatrix(double roll, double pitch, double yaw)
{
  double cr = std::cos(roll);
  double sr = std::sin(roll);
  double cp = std::cos(pitch);
  double sp = std::sin(pitch);
  double cy = std::cos(yaw);
  double sy = std::sin(yaw);

  Eigen::Matrix3d R;
  R << cy * cp, cy * sp * sr - sy * cr, cy * sp * cr + sy * sr,
      sy * cp, sy * sp * sr + cy * cr, sy * sp * cr - cy * sr,
      -sp, cp * sr, cp * cr;
  return R;
}

// Compute rotation matrix Rx(roll) * Ry(pitch)
Eigen::Matrix3d rotationMatrix(double roll, double pitch)
{
  double ct = std::cos(pitch);
  double st = std::sin(pitch);
  double cr = std::cos(roll);
  double sr = std::sin(roll);

  Eigen::Matrix3d R;
  R << ct, st * sr, st * cr,
      0, cr, -sr,
      -st, ct * sr, ct * cr;

  return R;
}

// Compute cost function: squared error
double costFunction(const Eigen::Vector3d &v1, const Eigen::Vector3d &v2, double roll, double pitch)
{
  Eigen::Matrix3d R    = rotationMatrix(roll, pitch);
  Eigen::Vector3d diff = R * v1 - v2;
  return diff.squaredNorm();
}
} // namespace geometry
} // namespace bmath