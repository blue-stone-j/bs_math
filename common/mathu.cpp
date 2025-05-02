
#include "common/mathu.h"

namespace bmath
{
int transformLine(const LineModel &model_in, LineModel &model_out, const Eigen::Affine3d &pose)
{
  Eigen::Vector4d pos_in(model_in.x, model_in.y, model_in.z, 1), pos_out;
  pos_out     = pose.matrix() * pos_in;
  model_out.x = pos_out(0);
  model_out.y = pos_out(1);
  model_out.z = pos_out(2);

  Eigen::Vector3d rot_in(model_in.a, model_in.b, model_in.c), rot_out;
  rot_out     = pose.matrix().block<3, 3>(0, 0) * rot_in;
  model_out.a = rot_out(0);
  model_out.b = rot_out(1);
  model_out.c = rot_out(2);

  return 0;
}

int transformPlane(const PlaneModel &model_in, PlaneModel &model_out,
                   const Eigen::Affine3d &pose)
{
  Eigen::Matrix3d R_inv = pose.matrix().block<3, 3>(0, 0).transpose();
  Eigen::Vector3d rot_in(model_in.a, model_in.b, model_in.c);
  Eigen::Vector3d rot_out = R_inv * rot_in;

  model_out.a = rot_out(0);
  model_out.b = rot_out(1);
  model_out.c = rot_out(2);
  model_out.d = model_in.d - rot_out.dot(pose.matrix().block<3, 1>(0, 3));

  return 0;
} // namespace Eigen::Affine3d&pose)
} // namespace bmath