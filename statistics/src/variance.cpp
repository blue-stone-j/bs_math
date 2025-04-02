
#include "variance.h"

namespace math
{
namespace statistics
{
float computeVariance(const Eigen::VectorXf &vector)
{
  float mean           = vector.mean();
  Eigen::VectorXf diff = vector.array() - mean;
  return diff.squaredNorm() / vector.size();
}
} // namespace statistics
} // namespace math