
/*
map points on the perimeter of a circle to the perimeter of its circumscribed square.
The circumscribed square has half-side length equal to the circle's radius.
*/

#include <cmath>
#include <utility>

// Simple mapping: project circle perimeter point (x, y) to square along the ray from origin.

/**
 * construct a ray from the origin through point (x, y) on the circle perimeter,
 * take the intersection with the circumscribed square as the mapped point.
 */
inline double sgn(double v) { return (v > 0) - (v < 0); }
std::pair<double, double> circlePointToCircumscribedSquare(double x, double y, double r)
{
  const double ax = std::abs(x);
  const double ay = std::abs(y);

  // Handle the trivial origin case defensively (shouldn't happen for perimeter points)
  if (ax == 0.0 && ay == 0.0)
  {
    return {0.0, 0.0};
  }

  if (ax >= ay)
  {
    // Hit the vertical side: X = ±r
    const double X = r * sgn(x);
    const double Y = (ax > 0.0) ? r * (y / ax) : 0.0;
    return {X, Y};
  }
  else
  {
    // Hit the horizontal side: Y = ±r
    const double Y = r * sgn(y);
    const double X = (ay > 0.0) ? r * (x / ay) : 0.0;
    return {X, Y};
  }
}



// Map a circle perimeter point (x, y) with radius r to an evenly-spaced point on the
// perimeter of the circumscribed square (half-side = r), by equal-perimeter parameterization.
// Start point is (r, 0) and direction is CCW(counter-clockwise). To change start/handedness, adjust `phase` and `ccw`.
struct Vec2
{
  double x;
  double y;
};
Vec2 circleToSquareUniformPerimeter(double x, double y, double r, double phase = 0.0, bool ccw = true)
{
  // 1) angle in [0, 2π)
  double theta = std::atan2(y, x); // (-π, π]
  if (theta < 0.0)
  {
    theta += 2.0 * M_PI; // [0, 2π)
  }

  // Optional: apply a phase shift and orientation
  // phase is in radians; ccw=false flips direction
  double theta_adj = ccw ? (theta + phase) : (2.0 * M_PI - std::fmod(theta + phase, 2.0 * M_PI));
  if (theta_adj >= 2.0 * M_PI) theta_adj -= 2.0 * M_PI;

  // 2) perimeter fraction and arclength along the square
  const double L = 8.0 * r;                  // circumscribed square perimeter
  const double p = theta_adj / (2.0 * M_PI); // [0, 1) proportion of circle perimeter
  double s       = p * L;                    // [0, 8r)

  // 3) piecewise conversion: traverse CCW starting at (r, 0)
  if (s < r)
  { // up right edge from y=0 -> y=+r
    return {r, s};
  }
  else if (s < 3.0 * r)
  { // left along top edge from x=+r -> x=-r (length 2r)
    double t = s - r;
    return {r - t, r};
  }
  else if (s < 5.0 * r)
  { // down left edge from y=+r -> y=-r (length 2r)
    double t = s - 3.0 * r;
    return {-r, r - t};
  }
  else if (s < 7.0 * r)
  { // right along bottom edge from x=-r -> x=+r (length 2r)
    double t = s - 5.0 * r;
    return {-r + t, -r};
  }
  else
  { // up right edge from y=-r -> y=0 (length r)
    double t = s - 7.0 * r;
    return {r, -r + t};
  }
}



// Map a 3D point P on a circular arc to the perimeter of the circumscribed square
// lying in the same plane, with uniform spacing along the square relative to arc length.
struct Vec3
{
  double x, y, z;
};

static inline Vec3 add(const Vec3 &a, const Vec3 &b) { return {a.x + b.x, a.y + b.y, a.z + b.z}; }
static inline Vec3 sub(const Vec3 &a, const Vec3 &b) { return {a.x - b.x, a.y - b.y, a.z - b.z}; }
static inline Vec3 mul(const Vec3 &a, double s) { return {a.x * s, a.y * s, a.z * s}; }
static inline double dot3(const Vec3 &a, const Vec3 &b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
static inline Vec3 cross3(const Vec3 &a, const Vec3 &b)
{
  return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}
static inline double norm3(const Vec3 &a)
{
  return std::sqrt(dot3(a, a));
}
static inline Vec3 normalize3(const Vec3 &a)
{
  double n = norm3(a);
  return n > 0 ? mul(a, 1.0 / n) : Vec3{0, 0, 0};
}
static inline double wrap2pi(double a)
{
  // return angle in [0, 2π)
  const double TWO_PI = 2.0 * M_PI;
  a                   = std::fmod(a, TWO_PI);
  if (a < 0) a += TWO_PI;
  return a;
}

// Build an orthonormal basis {U,V} in the plane with normal N.
// U is chosen deterministically to avoid degeneracy; V = N × U.
static inline void makePlaneBasis(const Vec3 &N_in, Vec3 &U, Vec3 &V, Vec3 &N)
{
  N = normalize3(N_in);
  // Pick the axis least aligned with N
  Vec3 A = (std::fabs(N.x) < 0.5) ? Vec3{1, 0, 0} : (std::fabs(N.y) < 0.5) ? Vec3{0, 1, 0} : Vec3{0, 0, 1};
  U      = normalize3(cross3(N, A));
  V      = cross3(N, U); // already unit if N and U are unit and orthogonal
}

// Convert 3D point P on the arc to its angle theta in the plane basis {U,V}.
// Angle is measured from U toward V (CCW around +N), in [0, 2π).
static inline double pointAngleOnCircle(const Vec3 &C, const Vec3 &U, const Vec3 &V,
                                        const Vec3 &P, double r)
{
  Vec3 d   = sub(P, C);
  double x = dot3(d, U);
  double y = dot3(d, V);
  // If P may be slightly off radius, we still just use atan2
  double theta = std::atan2(y, x); // (-π, π]
  return wrap2pi(theta);
}

// Walk arclength s ∈ [0, 8r) CCW on the square (half-side = r) in local 2D plane.
static inline Vec2 squarePointFromArclength(double s, double r)
{
  const double L = 8.0 * r;
  s              = std::fmod(s, L);
  if (s < 0) s += L;

  if (s < r)
  { // up right edge: (r, 0)->(r, r)
    return {r, s};
  }
  else if (s < 3.0 * r)
  { // top edge: (r, r)->(-r, r)
    double t = s - r;
    return {r - t, r};
  }
  else if (s < 5.0 * r)
  { // left edge: (-r, r)->(-r, -r)
    double t = s - 3.0 * r;
    return {-r, r - t};
  }
  else if (s < 7.0 * r)
  { // bottom edge: (-r, -r)->(r, -r)
    double t = s - 5.0 * r;
    return {-r + t, -r};
  }
  else
  { // up right edge: (r, -r)->(r, 0)
    double t = s - 7.0 * r;
    return {r, -r + t};
  }
}

/**
 * Map a 3D point P on a circular arc to the perimeter of the circumscribed square
 * lying in the same plane, with uniform spacing along the square relative to arc length.
 *
 * Inputs:
 *   C       - circle center (3D)
 *   N       - circle plane normal (3D, need not be unit)
 *   r       - circle radius (>0), equals square half-side
 *   theta0  - start angle of the arc in the plane basis (radians, [0,2π))
 *   dtheta  - sweep of the arc (radians), positive for CCW, negative for CW(clockwise)
 *   P       - 3D point on the arc to map
 *   s0      - starting arclength offset on the square perimeter (0 ≤ s0 < 8r). Default 0 starts at (r,0).
 *   cover_full_square - if true, map the arc to cover the entire square perimeter [0,8r);
 *                       if false, map proportionally: segment length = |dtheta|/(2π) * 8r.
 *
 * Returns:
 *   Q       - corresponding 3D point on the square perimeter.
 */
static inline Vec3 map3DArcPointToSquarePerimeter(const Vec3 &C, const Vec3 &N,
                                                  double r,
                                                  double theta0, double dtheta,
                                                  const Vec3 &P,
                                                  double s0              = 0.0,
                                                  bool cover_full_square = false)
{
  // 1) Plane basis
  Vec3 U, V, Nn;
  makePlaneBasis(N, U, V, Nn);

  // 2) Angle of P
  double thetaP = pointAngleOnCircle(C, U, V, P, r);

  // 3) Arc parameter t ∈ [0,1] along the arc
  //    Compute signed angular distance from theta0 to thetaP along the chosen sweep direction.
  const double TWO_PI = 2.0 * M_PI;
  theta0              = wrap2pi(theta0);
  double sweep        = dtheta;    // may be positive or negative
  if (sweep == 0.0) sweep = 1e-12; // avoid division by zero

  // Signed delta from theta0 to thetaP wrapped into (-π, π]
  double delta = thetaP - theta0;
  // Wrap into (-π, π]
  delta = std::fmod(delta + M_PI, TWO_PI);
  if (delta < 0) delta += TWO_PI;
  delta -= M_PI;

  // Project delta onto the sweep direction and normalize to t in [0,1]
  // Clamp to [0,1] in case P is slightly outside the arc due to noise.
  double t = delta / sweep; // works for both signs of sweep
  t        = std::clamp(t, 0.0, 1.0);

  // 4) Convert t to square arclength s
  const double L = 8.0 * r;
  double S       = cover_full_square ? L : (L * std::fabs(sweep) / TWO_PI); // arc maps to S on square
  double s       = s0 + t * S;
  // Optionally wrap s to [0, L)
  s = std::fmod(s, L);
  if (s < 0) s += L;

  // 5) Point on square in plane coordinates, then back to 3D
  Vec2 q2 = squarePointFromArclength(s, r);
  Vec3 Q  = add(C, add(mul(U, q2.x), mul(V, q2.y)));
  return Q;
}