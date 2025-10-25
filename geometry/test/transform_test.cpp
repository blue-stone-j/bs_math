
#include <gtest/gtest.h>

#include "geometry/transform/transform.h"

TEST(transform_test, test1)
{
  Eigen::Vector3d v1_raw(0.37, -0.02, 0.92);
  Eigen::Vector3d v2_raw(0.33, 0.03, 1.0);

  Eigen::Vector3d v1 = bmath::geometry::normalize(v1_raw);
  Eigen::Vector3d v2 = bmath::geometry::normalize(v2_raw);

  double pitch = 0.0, roll = 0.0;
  double learning_rate = 1e-2;
  double epsilon       = 1e-7;
  int max_iters        = 1000;

  for (int iter = 0; iter < max_iters; ++iter)
  {
    // Finite difference gradient
    double h = 1e-6;

    double f       = bmath::geometry::costFunction(v1, v2, roll, pitch);
    double f_pitch = bmath::geometry::costFunction(v1, v2, roll, pitch + h);
    double f_roll  = bmath::geometry::costFunction(v1, v2, roll + h, pitch);

    double grad_pitch = (f_pitch - f) / h;
    double grad_roll  = (f_roll - f) / h;

    // Update
    pitch -= learning_rate * grad_pitch;
    roll -= learning_rate * grad_roll;

    if (std::sqrt(grad_pitch * grad_pitch + grad_roll * grad_roll) < epsilon)
      break;
  }

  std::cout << "Final pitch (rad): " << pitch << ", roll (rad): " << roll << std::endl;
  std::cout << "Final pitch (deg): " << pitch * 180.0 / M_PI << ", roll (deg): " << roll * 180.0 / M_PI << std::endl;

  // Check final rotation
  Eigen::Matrix3d R      = bmath::geometry::rotationMatrix(roll, pitch);
  Eigen::Vector3d result = R * v1;
  std::cout << "Rotated v1: " << result.transpose() << std::endl;
  std::cout << "Target v2:  " << v2.transpose() << std::endl;
  std::cout << "Error norm: " << (result - v2).norm() << std::endl;
}