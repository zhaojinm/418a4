#include "triangle_triangle_intersection.h"
#include "Ray.h"
#include "ray_intersect_triangle.h"
bool triangle_triangle_intersection(
  const Eigen::RowVector3d & A0,
  const Eigen::RowVector3d & A1,
  const Eigen::RowVector3d & A2,
  const Eigen::RowVector3d & B0,
  const Eigen::RowVector3d & B1,
  const Eigen::RowVector3d & B2)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  double t;
  bool hit1 = ray_intersect_triangle(Ray(B1,B0-B1),A0,A1,A2,0,1,t);
  bool hit2 = ray_intersect_triangle(Ray(B2,B1-B2),A0,A1,A2,0,1,t);
  bool hit3 = ray_intersect_triangle(Ray(B0,B2-B0),A0,A1,A2,0,1,t);
  bool hit4 = ray_intersect_triangle(Ray(A1,A0-A1),B0,B1,B2,0,1,t);
  bool hit5 = ray_intersect_triangle(Ray(A2,A1-A2),B0,B1,B2,0,1,t);
  bool hit6 = ray_intersect_triangle(Ray(A0,A2-A0),B0,B1,B2,0,1,t);
  return hit1 || hit2 || hit3 || hit4 || hit5 || hit6;
  ////////////////////////////////////////////////////////////////////////////
}
