
#ifndef STATISTICS_VARIANCE_H
#define STATISTICS_VARIANCE_H

#include <Eigen/Dense>

namespace math
{
namespace statistics
{
float computeVariance(const Eigen::VectorXf &vec);
} // namespace statistics
} // namespace math

#endif