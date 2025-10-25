/*
calculate a circle in 3D space that
1. pass through a given point P
2. are tangent to two non-parallel planes
Π1: 𝑛1⋅𝑥+𝑑1=0
Π2: 𝑛2⋅𝑥+𝑑2=0
*/

#include <Eigen/Dense>
#include <vector>
#include <optional>
#include <cmath>
#include <limits>
#include <iostream>

struct Circle3D
{
  Eigen::Vector3d center;  // C
  Eigen::Vector3d plane_n; // unit normal of circle plane (u)
  double radius;           // r
};

namespace detail
{
inline bool nearlyZero(double v, double eps = 1e-12)
{
  return std::abs(v) <= eps;
}

// Solve a*x + b*y + c = 0 and (A1 x + B1 y + C1)^2 = L1^2 (x^2 + y^2).
// We substitute y from the line into the quadratic and solve the resulting quadratic in x.
// Robustly handles b ≈ 0 by swapping roles.
inline void solveOnBisectorLine(double a, double b, double c,
                                double A1, double B1, double C1, double L1,
                                std::vector<Eigen::Vector2d> &sols)
{
  // If the line is degenerate, skip.
  if (nearlyZero(a) && nearlyZero(b)) return;

  auto solve_with_y_of_x = [&](void) {
    // y = (-a x - c)/b
    const double invb = 1.0 / b;
    // Build quadratic in x for: (A1 x + B1 y + C1)^2 = L1^2 (x^2 + y^2)
    // y = p*x + q
    const double p = -a * invb;
    const double q = -c * invb;

    // Left side: (A1 x + B1 (p x + q) + C1)^2 = ( (A1 + B1 p) x + (B1 q + C1) )^2
    const double Llin = (A1 + B1 * p);
    const double Lcon = (B1 * q + C1);

    // Right side: L1^2 ( x^2 + (p x + q)^2 ) = L1^2 ( (1 + p^2) x^2 + 2 p q x + q^2 )
    const double Rxx = L1 * L1 * (1.0 + p * p);
    const double Rx  = L1 * L1 * (2.0 * p * q);
    const double Rc  = L1 * L1 * (q * q);

    // Bring all to left: (Llin x + Lcon)^2 - (Rxx x^2 + Rx x + Rc) = 0
    // => (Llin^2 - Rxx) x^2 + (2 Llin Lcon - Rx) x + (Lcon^2 - Rc) = 0
    const double qa = Llin * Llin - Rxx;
    const double qb = 2.0 * Llin * Lcon - Rx;
    const double qc = Lcon * Lcon - Rc;

    const double disc = qb * qb - 4.0 * qa * qc;

    auto push_solution = [&](double x) {
      double y = p * x + q;
      sols.emplace_back(x, y);
    };

    if (nearlyZero(qa))
    {
      // Linear case: qb x + qc = 0
      if (!nearlyZero(qb))
      {
        push_solution(-qc / qb);
      }
      return;
    }

    // no real solutions (robust)
    if (disc < -1e-12)
    {
      return;
    }

    // One (double) root due to numerical roundoff
    if (disc < 0)
    {
      double x = -qb / (2.0 * qa);
      push_solution(x);
      return;
    }

    double sqrtD = std::sqrt(std::max(0.0, disc));
    double x1    = (-qb - sqrtD) / (2.0 * qa);
    double x2    = (-qb + sqrtD) / (2.0 * qa);
    push_solution(x1);
    if (std::abs(x2 - x1) > 1e-12)
    {
      push_solution(x2);
    }
  };

  auto solve_with_x_of_y = [&](void) {
    // x = (-b y - c)/a
    const double inva = 1.0 / a;
    const double p    = -b * inva; // x = p*y + q
    const double q    = -c * inva;

    // Substitute into quadratic
    // Left: (A1 (p y + q) + B1 y + C1)^2 = ( (A1 p + B1) y + (A1 q + C1) )^2
    const double Llin = (A1 * p + B1);
    const double Lcon = (A1 * q + C1);

    // Right: L1^2 ( (p y + q)^2 + y^2 ) = L1^2 ( (p^2 + 1) y^2 + 2 p q y + q^2 )
    const double Ryy = L1 * L1 * (p * p + 1.0);
    const double Ry  = L1 * L1 * (2.0 * p * q);
    const double Rc  = L1 * L1 * (q * q);

    // Quadratic in y
    const double qa = Llin * Llin - Ryy;
    const double qb = 2.0 * Llin * Lcon - Ry;
    const double qc = Lcon * Lcon - Rc;

    const double disc = qb * qb - 4.0 * qa * qc;

    auto push_solution = [&](double y) {
      double x = p * y + q;
      sols.emplace_back(x, y);
    };

    if (nearlyZero(qa))
    {
      if (!nearlyZero(qb)) push_solution(-qc / qb);
      {
        return;
      }
    }

    if (disc < -1e-12)
    {
      return;
    }

    if (disc < 0)
    {
      double y = -qb / (2.0 * qa);
      push_solution(y);
      return;
    }

    double sqrtD = std::sqrt(std::max(0.0, disc));
    double y1    = (-qb - sqrtD) / (2.0 * qa);
    double y2    = (-qb + sqrtD) / (2.0 * qa);
    push_solution(y1);
    if (std::abs(y2 - y1) > 1e-12)
    {
      push_solution(y2);
    }
  };

  if (!nearlyZero(b))
  {
    solve_with_y_of_x();
  }
  else
  {
    solve_with_x_of_y();
  }
}
} // namespace detail

// Main solver
inline std::vector<Circle3D> findCirclesThroughPointTangentToTwoPlanes(const Eigen::Vector3d &n1, double d1,
                                                                       const Eigen::Vector3d &n2, double d2,
                                                                       const Eigen::Vector3d &P,
                                                                       double eps = 1e-10)
{
  std::vector<Circle3D> out;

  // 0) Pre-check: planes must be non-parallel
  Eigen::Vector3d cross = n1.cross(n2);
  double crossN         = cross.norm();
  if (detail::nearlyZero(crossN, 1e-14))
  {
    // Planes nearly parallel: undefined for this construction
    return out;
  }

  // 1) Circle plane normal u, ONB (e1, e2) for that plane
  // In 3D geometry, an ONB is a set of three mutually perpendicular unit vectors that form a local coordinate frame.
  Eigen::Vector3d u = cross / crossN; // unit
  // π₍c₎ (pronounced “pi-sub-c”) denotes the "plane of the circle" we are solving for.
  // Choose e1 in plane πc: project n1 onto πc as a stable direction
  Eigen::Vector3d e1 = n1 - (n1.dot(u)) * u;
  double e1n         = e1.norm();
  if (detail::nearlyZero(e1n))
  {
    // n1 parallel to u; fall back to using an arbitrary vector not collinear with u
    Eigen::Vector3d tmp(1.0, 0.0, 0.0);
    if (std::abs(u.x()) > 0.9) tmp = Eigen::Vector3d(0.0, 1.0, 0.0);
    e1 = (tmp - (tmp.dot(u)) * u).normalized();
  }
  else
  {
    e1 /= e1n;
  }
  Eigen::Vector3d e2 = u.cross(e1); // completes ONB

  // 2) Intersections with πc as 2D lines Ai x + Bi y + Ci = 0 (origin at P)
  auto lineCoeffs = [&](const Eigen::Vector3d &n, double d) {
    double A = n.dot(e1);
    double B = n.dot(e2);
    double C = n.dot(P) + d; // constant term in plane coords
    double L = std::hypot(A, B);
    return std::tuple<double, double, double, double>(A, B, C, L);
  };

  double A1, B1, C1, L1;
  std::tie(A1, B1, C1, L1) = lineCoeffs(n1, d1);
  double A2, B2, C2, L2;
  std::tie(A2, B2, C2, L2) = lineCoeffs(n2, d2);

  // Degenerate if either intersection is "no line" in πc (L ~ 0)
  if (detail::nearlyZero(L1, eps) || detail::nearlyZero(L2, eps))
  {
    // πc is parallel to one plane -> the plane's intersection is all πc or none; skip
    return out;
  }

  // 3) For each sign s in {+1,-1}, build angle-bisector line:
  // (A1 - k A2) x + (B1 - k B2) y + (C1 - k C2) = 0, with k = s * (L1/L2).
  for (int sgn : {+1, -1})
  {
    double k = sgn * (L1 / L2);
    double a = (A1 - k * A2);
    double b = (B1 - k * B2);
    double c = (C1 - k * C2);

    // 4) Intersect that line with (A1 x + B1 y + C1)^2 = L1^2 (x^2 + y^2)
    std::vector<Eigen::Vector2d> centers2D;
    detail::solveOnBisectorLine(a, b, c, A1, B1, C1, L1, centers2D);

    // 5) Map solutions back to 3D and push if valid
    for (const auto &c2 : centers2D)
    {
      double cx = c2.x(), cy = c2.y();
      double r = std::sqrt(cx * cx + cy * cy);
      if (r <= eps) continue; // radius too small / numerical artifact

      Eigen::Vector3d C = P + cx * e1 + cy * e2;

      // Optional: verify tangency numerically
      auto distPlane = [&](const Eigen::Vector3d &n, double d) {
        return std::abs(n.dot(C) + d) / n.norm();
      };
      double r1 = distPlane(n1, d1);
      double r2 = distPlane(n2, d2);

      if (std::abs(r - r1) > 1e-6 || std::abs(r - r2) > 1e-6)
      {
        // Numerical reject if not matching within tolerance
        continue;
      }

      out.push_back({C, u, r});
    }
  } // endfor: sgn

  // Deduplicate near-duplicates
  const double centerTol = 1e-8;
  const double radTol    = 1e-8;
  std::vector<Circle3D> unique;
  for (auto &cir : out)
  {
    bool dup = false;
    for (auto &uc : unique)
    {
      if ((cir.center - uc.center).norm() < centerTol && std::abs(cir.radius - uc.radius) < radTol && (cir.plane_n - uc.plane_n).norm() < 1e-8)
      {
        dup = true;
        break;
      }
    }
    if (!dup)
    {
      unique.push_back(cir);
    }
  } // endfor: Deduplicate

  return unique;
}

int main()
{
  // Planes: n·x + d = 0
  Eigen::Vector3d n1(0, 1, 0);
  double d1 = 0.0; // z = 1
  Eigen::Vector3d n2(1, 0, 0);
  n2.normalize();
  double d2 = 0.0;                  // an oblique plane
  Eigen::Vector3d P(1.0, 1.0, 0.0); // point

  auto sols = findCirclesThroughPointTangentToTwoPlanes(n1, d1, n2, d2, P);

  std::cout << "Found " << sols.size() << " circle(s)\n";
  for (std::size_t i = 0; i < sols.size(); ++i)
  {
    const auto &c = sols[i];
    std::cout << "Circle " << i << ":\n";
    std::cout << "  center = [" << c.center.transpose() << "]\n";
    std::cout << "  plane_n= [" << c.plane_n.transpose() << "]\n";
    std::cout << "  radius = " << c.radius << "\n";
  }
  return 0;
}
