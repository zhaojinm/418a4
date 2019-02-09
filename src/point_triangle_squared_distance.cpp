#include "point_triangle_squared_distance.h"
#include <Eigen/Core>
#include <Eigen/Geometry>

double point_triangle_squared_distance(
  const Eigen::RowVector3d & query,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  Eigen::RowVector3d & bary)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here
  //reference : http://box2d.org/files/GDC2010/GDC2010_Catto_Erin_GJK.pdf start from page32

  //compute alpha beta gamma and projection
  Eigen::RowVector3d ba = B-A;
  Eigen::RowVector3d ca = C-A;
  Eigen::RowVector3d normal = ba.cross(ca);
  Eigen::RowVector3d w = query - A;
  double gamma = std::fabs((ba.cross(w)).dot(normal))/normal.dot(normal);
  double beta = std::fabs((w.cross(ca)).dot(normal))/normal.dot(normal);
  double alpha = 1 - gamma - beta;
  normal.normalize();
  double distance = w.dot(normal);
  Eigen::RowVector3d projection = query-distance*(normal);

  // if projection inside triangle
  if (alpha>=0 && alpha<=1 && beta>=0 && beta<=1 && gamma>=0 && gamma <=1) {
    bary(0) = alpha;
    bary(1) = beta;
    bary(2) = gamma;
    projection = alpha*A + beta*B + gamma*C;
    return (query-projection).squaredNorm();
  }
  // compute distance to 3 line segments(side)
  double t1 = fmin(1,fmax(0,(B-A).dot(projection-A)));
  Eigen::RowVector3d c1 = A+t1*(B-A);
  double t2 = fmin(1,fmax(0,(C-A).dot(projection-A)));
  Eigen::RowVector3d c2 = A+t2*(C-A);
  double t3 = fmin(1,fmax(0,(C-B).dot(projection-B)));
  Eigen::RowVector3d c3 = B+t3*(C-B);
  
  // find minimun distance to 3 line segments
  Eigen::RowVector3d min_ = c1;
  if ((query-c2).squaredNorm()<(query-c1).squaredNorm() &&
      (query-c2).squaredNorm()<(query-c3).squaredNorm())
      min_ = c2;
  if ((query-c3).squaredNorm()<(query-c1).squaredNorm() &&
      (query-c3).squaredNorm()<(query-c2).squaredNorm())
      min_ = c3;

  //compute bary
  double a = A(0), b = A(1), c = A(2);
  double d = B(0), e = B(1), f = B(2);
  double g = C(0), h = C(1), i = C(2);
  double j = min_(0), k = min_(1), l = min_(2);
  double M = a*(e*i-h*f)+b*(g*f-d*i)+c*(d*h-e*g);
  bary(0) = (j*(e*i-h*f)+k*(g*f-d*i)+l*(d*h-e*g))/M;
  bary(1) = (i*(a*k-j*b)+h*(j*c-a*l)+g*(b*l-k*c))/M;
  bary(2) = -(f*(a*k-j*b)+e*(j*c-a*l)+d*(b*l-k*c))/M;
  //return squared distance
  return (query-min_).squaredNorm();
  ////////////////////////////////////////////////////////////////////////////
}
