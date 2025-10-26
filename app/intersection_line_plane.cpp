/*
calculates the intersection point of a line and a plane in 3D space.
The line is defined by a point p0 and a direction vector d.
The plane is defined by a point q0 and a normal vector n.
The function returns true if there is a unique intersection point,
false if the line is parallel to the plane (either no intersection or infinite intersections).
*/


#include <iostream>
#include <Eigen/Dense> // Convenient for vector operations

bool linePlaneIntersection(
    const Eigen::Vector3d &p0, // Line point
    const Eigen::Vector3d &d,  // Line direction
    const Eigen::Vector3d &q0, // Plane point
    const Eigen::Vector3d &n,  // Plane normal
    Eigen::Vector3d &intersection)
{
  double denom = n.dot(d);
  if (std::abs(denom) < 1e-9)
  {
    // Line parallel to plane
    if (std::abs(n.dot(p0 - q0)) < 1e-9)
    {
      // Line lies in plane
      return false; // Infinite solutions
    }
    return false; // No intersection
  }
  double t     = -n.dot(p0 - q0) / denom;
  intersection = p0 + t * d;
  return true; // One intersection
}

int main()
{
  Eigen::Vector3d p0(1, 2, 3);
  Eigen::Vector3d d(0, 0, 1);
  Eigen::Vector3d q0(0, 0, 0);
  Eigen::Vector3d n(0, 0, 1);

  Eigen::Vector3d intersection;
  if (linePlaneIntersection(p0, d, q0, n, intersection))
  {
    std::cout << "Intersection: " << intersection.transpose() << std::endl;
  }
  else
  {
    std::cout << "No unique intersection" << std::endl;
  }
}
