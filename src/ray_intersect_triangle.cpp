#include "ray_intersect_triangle.h"

bool ray_intersect_triangle(
  const Ray & ray,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  const double min_t,
  const double max_t,
  double & t)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  Eigen::RowVector3d t1 = A-B, t2 = A-C;
  double a = t1[0], b=t1[1], c=t1[2];
  double d = t2[0], e=t2[1], f=t2[2];
  double g = ray.direction[0], h=ray.direction[1], i=ray.direction[2];
  double j = A[0]-ray.origin[0], k=A[1]-ray.origin[1], l=A[2]-ray.origin[2];
  double common = a*(e*i-h*f) + b*(g*f-d*i) + c*(d*h-e*g);
  double beta = (j*(e*i-h*f) + k*(g*f-d*i) + l*(d*h-e*g))/common;
  double gamma = (i*(a*k -j*b) + h*(j*c-a*l) + g*(b*l-k*c))/common;
  t = -(f*(a*k-j*b) + e*(j*c-a*l) + d*(b*l-k*c))/common;
  if (t<min_t || t>max_t) return false;
  if (gamma<0 || beta<0 || gamma>1 || beta>1 || gamma+beta>1)
    return false;
  return true;
  ////////////////////////////////////////////////////////////////////////////
}
