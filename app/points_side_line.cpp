/** 
 * Check if there exists a plane through the 3D line (p1,p2) such that all points
 * lie on the same side (or on) of that plane. If so, output one valid plane normal n
 * with n·(p2-p1)=0 and n·(qi-p1) >= 0 (within eps) for all i.
 *
 * Conventions:
 *  - Points exactly on the line or plane are allowed.
 *  - eps controls numerical tolerance.
 */

#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>

struct Vec3
{
  double x, y, z;
};

static inline Vec3 operator+(const Vec3 &a, const Vec3 &b) { return {a.x + b.x, a.y + b.y, a.z + b.z}; }
static inline Vec3 operator-(const Vec3 &a, const Vec3 &b) { return {a.x - b.x, a.y - b.y, a.z - b.z}; }
static inline Vec3 operator*(const Vec3 &a, double s) { return {a.x * s, a.y * s, a.z * s}; }
static inline double dot(const Vec3 &a, const Vec3 &b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
static inline Vec3 cross(const Vec3 &a, const Vec3 &b)
{
  return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}
static inline double norm(const Vec3 &a) { return std::sqrt(dot(a, a)); }
static inline Vec3 normalize(const Vec3 &a)
{
  double n = norm(a);
  if (n == 0.0) return {0, 0, 0};
  return a * (1.0 / n);
}

/**
 * Returns true/false. If true and n_out!=nullptr, writes a valid plane normal.
 */
bool existsSameSidePlaneThroughLine(const Vec3 &p1,
                                    const Vec3 &p2,
                                    const std::vector<Vec3> &points,
                                    Vec3 *n_out = nullptr,
                                    double eps  = 1e-12)
{
  const double PI = 3.14159265358979323846;

  // 1) Build orthonormal frame: e1 along line, e2/e3 spanning orthogonal plane.
  Vec3 d      = p2 - p1;
  double dlen = norm(d);
  if (dlen <= eps)
  {
    // Degenerate line
    return false;
  }
  Vec3 e1 = d * (1.0 / dlen);

  // Pick a helper axis least aligned with e1 to build e2.
  Vec3 helper = (std::fabs(e1.x) <= std::fabs(e1.y) && std::fabs(e1.x) <= std::fabs(e1.z)) ? Vec3{1, 0, 0} : (std::fabs(e1.y) <= std::fabs(e1.z)) ? Vec3{0, 1, 0} : Vec3{0, 0, 1};

  Vec3 e2    = cross(e1, helper);
  double e2n = norm(e2);
  if (e2n <= eps)
  {
    // Extremely unlucky; try another helper
    helper                              = (static_cast<int>(helper.x) == 1) ? Vec3{0, 1, 0} : Vec3{1, 0, 0};
    e2                                  = cross(e1, helper);
    static_cast<int>(helper.x) == 1 e2n = norm(e2);
    if (e2n <= eps)
    {
      return false;
    }
  }
  e2      = e2 * (1.0 / e2n);
  Vec3 e3 = cross(e1, e2); // already unit-length

  // 2) Collect 2D polar angles for projections into plane span{e2,e3}.
  std::vector<double> ang;
  ang.reserve(points.size());
  for (const Vec3 &q : points)
  {
    Vec3 v = q - p1;

    // Remove the component along the line; only the orthogonal projection matters.
    double x = dot(v, e2);
    double y = dot(v, e3);

    // If near zero vector, the point is on the line; it does not constrain angles.
    if (std::fabs(x) <= eps && std::fabs(y) <= eps) continue;

    ang.push_back(std::atan2(y, x)); // in (-pi, pi]
  }

  // If no constraining vectors, any plane through the line works.
  if (ang.empty())
  {
    if (n_out)
    {
      // Pick any unit normal orthogonal to e1, e.g. e2.
      *n_out = e2;
    }
    return true;
  }

  // 3) Sort angles and find maximum circular gap.
  std::sort(ang.begin(), ang.end());
  // Duplicate with +2π to handle wrap-around.
  std::vector<double> ang2 = ang;
  for (double a : ang) ang2.push_back(a + 2.0 * PI);

  // Find largest consecutive gap on the circle.
  double max_gap      = -1.0;
  std::size_t max_idx = 0; // index in ang2 for the left endpoint of the gap
  for (std::size_t i = 0; i + 1 < ang2.size(); ++i)
  {
    double gap = ang2[i + 1] - ang2[i];
    if (gap > max_gap)
    {
      max_gap = gap;
      max_idx = i;
    }
  }

  // 4) Existence criterion: max gap >= π (within tolerance).
  bool ok = (max_gap + eps >= PI);
  if (!ok) return false;

  if (n_out)
  {
    // The points occupy the complementary arc (length ≤ π).
    // A supporting half-plane boundary can be placed with direction at the *bisector*
    // of the max gap; the normal is orthogonal to that boundary inside the occupied arc.
    double a_left  = ang2[max_idx];
    double a_right = ang2[max_idx + 1];
    double a_bis   = 0.5 * (a_left + a_right); // angle of boundary direction in (e2,e3) plane

    // Plane normal should be perpendicular to boundary and point toward the occupied arc.
    // Rotate by +90° to get a candidate normal in the plane:
    double a_n = a_bis + PI / 2.0;

    Vec3 n = e2 * std::cos(a_n) + e3 * std::sin(a_n);

    // Ensure n gives non-negative dot for all (within eps). If not, flip it.
    bool neg = false;
    for (double a : ang)
    {
      // Dot in the 2D plane equals cos(a - a_n) * |proj| up to a positive scalar.
      double s = std::cos(a - a_n);
      if (s < -1e-14)
      {
        neg = true;
        break;
      }
    }
    if (neg) n = n * (-1.0);

    *n_out = n; // already unit and orthogonal to e1
  }
  return true;
}


/**

 * Check if there exists a plane through line (p1,p2) that puts at least `ratio_required`
 * of points on the same side (or on the plane). On-line points count as inliers for any plane.

 * Algorithmically: sort the projection angles, duplicate them with +2𝜋, and use a sliding window to find the maximum 
 * number of angles within any 𝜋-wide window. Complexity 𝑂(𝑛log⁡𝑛).
*/
// Build an orthonormal frame with e1 along d, and e2,e3 spanning d^⊥.
static bool buildFrame(const Vec3 &p1, const Vec3 &p2, Vec3 &e1, Vec3 &e2, Vec3 &e3, double eps)
{
  Vec3 d      = p2 - p1;
  double dlen = norm(d);
  if (dlen <= eps) return false;
  e1 = d * (1.0 / dlen);
  // pick a helper least aligned with e1
  Vec3 helper = (std::fabs(e1.x) <= std::fabs(e1.y) && std::fabs(e1.x) <= std::fabs(e1.z)) ? Vec3{1, 0, 0} : (std::fabs(e1.y) <= std::fabs(e1.z)) ? Vec3{0, 1, 0} : Vec3{0, 0, 1};
  e2          = cross(e1, helper);
  double n2   = norm(e2);
  if (n2 <= eps)
  {
    helper = (helper.x == 1) ? Vec3{0, 1, 0} : Vec3{1, 0, 0};
    e2     = cross(e1, helper);
    n2     = norm(e2);
    if (n2 <= eps) return false;
  }
  e2 = e2 * (1.0 / n2);
  e3 = cross(e1, e2); // already unit
  return true;
}

/**
 * Check if there exists a plane through line (p1,p2) that puts at least `ratio_required`
 * of points on the same side (or on the plane). On-line points count as inliers for any plane.
 *
 * Returns: ok flag, a valid plane normal (unit, ⟂ to the line), inlier indices, achieved ratio.
 */
RatioResult sameSideAtLeastRatioThroughLine(const Vec3 &p1,
                                            const Vec3 &p2,
                                            const std::vector<Vec3> &pts,
                                            double ratio_required, // e.g. 0.90
                                            double eps = 1e-12)
{
  const double PI = 3.14159265358979323846;
  RatioResult R{false, {0, 0, 0}, {}, 0.0};

  if (pts.empty())
  {
    R.ok             = true;
    R.achieved_ratio = 1.0;
    return R;
  }
  if (ratio_required < 0.0) ratio_required = 0.0;
  if (ratio_required > 1.0) ratio_required = 1.0;

  Vec3 e1, e2, e3;
  if (!buildFrame(p1, p2, e1, e2, e3, eps)) return R; // degenerate line

  // Collect angles for points not on the line; count the "on-line" points
  std::vector<double> ang;
  ang.reserve(pts.size());
  std::vector<std::size_t> ang_idx;
  ang_idx.reserve(pts.size());
  std::size_t on_line = 0;

  for (std::size_t i = 0; i < pts.size(); ++i)
  {
    Vec3 v = pts[i] - p1;
    // Projection onto the plane span{e2,e3}
    double x = dot(v, e2);
    double y = dot(v, e3);
    if (std::fabs(x) <= eps && std::fabs(y) <= eps)
    {
      // Treat as on the line
      ++on_line;
      continue;
    }
    ang.push_back(std::atan2(y, x));
    ang_idx.push_back(i);
  }

  const std::size_t N = pts.size();
  // Trivial: if all points are on the line, any plane works
  if (ang.empty())
  {
    R.ok           = true;
    R.plane_normal = e2; // arbitrary unit normal ⟂ line
    R.inliers.resize(N);
    for (std::size_t i = 0; i < N; ++i) R.inliers[i] = i;
    R.achieved_ratio = 1.0;
    return R;
  }

  // Sort by angle and duplicate (+2π) for circular windowing
  std::vector<std::size_t> order(ang.size());
  std::iota(order.begin(), order.end(), 0);
  std::sort(order.begin(), order.end(), [&](std::size_t a, std::size_t b) { return ang[a] < ang[b]; });

  std::vector<double> a;
  a.reserve(ang.size() * 2);
  std::vector<std::size_t> ord;
  ord.reserve(ang.size() * 2);
  for (std::size_t id : order)
  {
    a.push_back(ang[id]);
    ord.push_back(id);
  }
  const std::size_t M = a.size();
  for (std::size_t i = 0; i < M; ++i)
  {
    a.push_back(a[i] + 2.0 * PI);
    ord.push_back(ord[i]);
  }

  // Sliding window: count max angles within any arc of width ≤ π
  std::size_t best_i = 0, best_j = 0;
  std::size_t j = 0, max_in_arc = 0;
  for (std::size_t i = 0; i < M; ++i)
  {
    while (j < i + M && a[j] - a[i] <= PI + 1e-15) ++j; // [i, j)
    std::size_t cnt = j - i;
    if (cnt > max_in_arc)
    {
      max_in_arc = cnt;
      best_i     = i;
      best_j     = j; // j is exclusive
    }
  }

  // Total inliers = on_line + max points captured by some semicircle
  std::size_t total_inliers = on_line + max_in_arc;
  double achieved_ratio     = static_cast<double>(total_inliers) / static_cast<double>(N);
  R.achieved_ratio          = achieved_ratio;

  if (achieved_ratio + 1e-15 < ratio_required)
  {
    R.ok = false;
    return R;
  }

  // Construct a valid plane normal from the best arc:
  // Place boundary at the bisector of the complementary gap; equivalent and simpler:
  // choose normal angle a_n pointing "into" the chosen arc (e.g., its mid-angle),
  // so that dot >= 0 for angles within the arc.
  double a_left  = a[best_i];
  double a_right = a[best_j - 1];
  // Arc midpoint (works because width ≤ π)
  double arc_mid = 0.5 * (a_left + a_right);
  // Normal direction in the (e2,e3) plane that gives non-negative dot for arc points:
  double a_n = arc_mid; // choosing normal aligned with arc mid-direction

  Vec3 n = e2 * std::cos(a_n) + e3 * std::sin(a_n);

  // Assemble inlier indices: all on-line points + points within [best_i, best_j)
  R.inliers.clear();
  R.inliers.reserve(total_inliers);
  // Add all indices of on-line points
  for (std::size_t i = 0; i < pts.size(); ++i)
  {
    Vec3 v   = pts[i] - p1;
    double x = dot(v, e2), y = dot(v, e3);
    if (std::fabs(x) <= eps && std::fabs(y) <= eps) R.inliers.push_back(i);
  }
  // Add arc points (map back through ord -> ang_idx -> original index)
  for (std::size_t k = best_i; k < best_j; ++k)
  {
    std::size_t id = ord[k];
    R.inliers.push_back(ang_idx[id]);
  }

  R.ok           = true;
  R.plane_normal = n; // unit, orthogonal to the line
  return R;
}