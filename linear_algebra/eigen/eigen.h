
#ifndef EIGEN_H
#define EIGEN_H

namespace bmath
{
namespace linear_algebra
{
// Power iteration to find dominant eigenvector
template <typename Scalar>
void powerIteration(Scalar C[3][3], Scalar eigenvector[3], int max_iterations = 100, Scalar tol = 1e-6);

} // namespace linear_algebra
} // namespace bmath

#endif