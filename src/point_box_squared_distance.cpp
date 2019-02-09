#include "point_box_squared_distance.h"

double point_box_squared_distance(
  const Eigen::RowVector3d & query,
  const BoundingBox & box)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here
  Eigen::RowVector3d dis;
  dis(0) = fmax(fmax(query(0)-box.max_corner(0),0),box.min_corner(0)-query(0));
  dis(1) = fmax(fmax(query(1)-box.max_corner(1),0),box.min_corner(1)-query(1));
  dis(2) = fmax(fmax(query(2)-box.max_corner(2),0),box.min_corner(2)-query(2));
  return dis.squaredNorm();
  ////////////////////////////////////////////////////////////////////////////
}
