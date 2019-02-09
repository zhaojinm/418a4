#include "ray_intersect_box.h"
#include <iostream>

bool ray_intersect_box(
  const Ray & ray,
  const BoundingBox& box,
  const double min_t,
  const double max_t)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  double txmin,txmax,tymin,tymax,tzmin,tzmax;
  double xd = ray.direction(0),yd = ray.direction(1), zd = ray.direction(2);
  double xmin = box.min_corner(0),ymin = box.min_corner(1), zmin = box.min_corner(2);
  double xmax = box.max_corner(0),ymax = box.max_corner(1), zmax = box.max_corner(2);
  double xe = ray.origin(0),ye = ray.origin(1), ze = ray.origin(2);

  txmin = fmin((xmin-xe)/xd,(xmax-xe)/xd);
  txmax = fmax((xmin-xe)/xd,(xmax-xe)/xd);
  tymin = fmin((ymin-ye)/yd,(ymax-ye)/yd);
  tymax = fmax((ymin-ye)/yd,(ymax-ye)/yd);
  tzmin = fmin((zmin-ze)/zd,(zmax-ze)/zd);
  tzmax = fmax((zmin-ze)/zd,(zmax-ze)/zd);

  double over_lap_t_min = fmax(fmax(txmin,tymin),tzmin);
  double over_lap_t_max = fmin(fmin(txmax,tymax),tzmax);

  if (over_lap_t_max<over_lap_t_min) return false;
  if (fmin(max_t,over_lap_t_max)<fmax(min_t,over_lap_t_min)) return false;
  return true;
  ////////////////////////////////////////////////////////////////////////////
}
