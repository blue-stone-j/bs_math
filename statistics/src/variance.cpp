
#include <numeric>

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

double computeCovariance(const std::vector<double> &X, const std::vector<double> &Y)
{
  if (X.size() != Y.size() || X.empty())
  {
    throw std::invalid_argument("Vectors must be of the same size and non-empty.");
  }

  std::size_t N = X.size();

  // Compute means
  double mean_X = std::accumulate(X.begin(), X.end(), 0.0) / N;
  double mean_Y = std::accumulate(Y.begin(), Y.end(), 0.0) / N;

  // Compute covariance
  double covariance = 0.0;
  for (std::size_t i = 0; i < N; ++i)
  {
    covariance += (X[i] - mean_X) * (Y[i] - mean_Y);
  }
  return covariance / N; // For population covariance; use (N-1) for sample covariance
}
} // namespace statistics
} // namespace math