
#include "linear_algebra/eigen/eigen.h"

#include "common/mathu.h"

namespace bmath
{
namespace linear_algebra
{
template <typename Scalar>
void powerIteration(Scalar C[3][3], Scalar eigenvector[3], int max_iterations, Scalar tol)
{
  // Initial guess for eigenvector
  Scalar v[3] = {1, 1, 1};
  normalize(v);

  for (int iter = 0; iter < max_iterations; iter++)
  {
    Scalar new_v[3] = {0, 0, 0};

    // Matrix-vector multiplication
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        new_v[i] += C[i][j] * v[j];

    normalize(new_v);

    // Convergence check
    Scalar diff = fabs(v[0] - new_v[0]) + fabs(v[1] - new_v[1]) + fabs(v[2] - new_v[2]);
    if (diff < tol) break;

    // Update
    for (int i = 0; i < 3; i++)
      v[i] = new_v[i];
  }

  // Copy result
  for (int i = 0; i < 3; i++)
    eigenvector[i] = v[i];
}
} // namespace linear_algebra
} // namespace bmath