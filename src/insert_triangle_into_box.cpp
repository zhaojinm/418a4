#include "insert_triangle_into_box.h"

void insert_triangle_into_box(
  const Eigen::RowVector3d & a,
  const Eigen::RowVector3d & b,
  const Eigen::RowVector3d & c,
  BoundingBox & B)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////
	B.min_corner(0) = fmin(B.min_corner(0),fmin(fmin(a(0),b(0)),c(0)));
	B.min_corner(1) = fmin(B.min_corner(1),fmin(fmin(a(1),b(1)),c(1)));
	B.min_corner(2) = fmin(B.min_corner(2),fmin(fmin(a(2),b(2)),c(2)));
	B.max_corner(0) = fmax(B.max_corner(0),fmax(fmax(a(0),b(0)),c(0)));
	B.max_corner(1) = fmax(B.max_corner(1),fmax(fmax(a(1),b(1)),c(1)));
	B.max_corner(2) = fmax(B.max_corner(2),fmax(fmax(a(2),b(2)),c(2)));
}

