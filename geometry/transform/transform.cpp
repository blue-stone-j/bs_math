
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

// Compute rotation matrix Rx(roll) * Ry(pitch)
Eigen::Matrix3d rotationMatrix(double pitch, double roll)
{
  double cp = cos(pitch), sp = sin(pitch);
  double cr = cos(roll), sr = sin(roll);

  Eigen::Matrix3d R;
  R << cp, 0, sp,
      sr * sp, cr, -sr * cp,
      -cr * sp, sr, cr * cp;
  return R;
}

// Compute cost function: squared error
double costFunction(const Eigen::Vector3d &v1, const Eigen::Vector3d &v2, double pitch, double roll)
{
  Eigen::Matrix3d R    = rotationMatrix(pitch, roll);
  Eigen::Vector3d diff = R * v1 - v2;
  return diff.squaredNorm();
}
} // namespace geometry
} // namespace bmath