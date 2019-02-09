#include "ray_intersect_triangle_mesh_brute_force.h"
#include "ray_intersect_triangle.h"

bool ray_intersect_triangle_mesh_brute_force(
  const Ray & ray,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double min_t,
  const double max_t,
  double & hit_t,
  int & hit_f)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  hit_t = std::numeric_limits<double>::infinity();
  bool ret = false;
  for (int i=0;i<F.rows(); i++){
    double t;
    bool hit = ray_intersect_triangle(ray,V.row(F(i,0)),V.row(F(i,1)),V.row(F(i,2)),min_t,max_t,t);
    if (hit && t<hit_t){
      hit_t=t;
      hit_f=i;
      ret = true;
    }
  }
  return ret;
  ////////////////////////////////////////////////////////////////////////////
}
