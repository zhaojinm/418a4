#include "AABBTree.h"
#include "insert_box_into_box.h"

AABBTree::AABBTree(
  const std::vector<std::shared_ptr<Object> > & objects,
  int a_depth): 
  depth(std::move(a_depth)), 
  num_leaves(objects.size())
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////
  for (int i=0;i<objects.size();i++)
    insert_box_into_box(objects[i]->box, this->box);
  
  if (objects.size()==0){
  }else if (objects.size()==1){
    this->left = objects[0];
  }else if (objects.size()==2){
    this->left = objects[0];
    this->right = objects[1];
  }else{
    Eigen::RowVector3d range = this->box.max_corner -this->box.min_corner;
    int axis = 0;
    if (range(1)>=range(0) and range(1)>=range(2))
      axis = 1;
    if (range(2)>=range(0) and range(2)>=range(1))
      axis = 2;
    double mid = this->box.center()(axis);
    std::vector<std::shared_ptr<Object>> left_objects,right_objects;
    for (int i=0;i<objects.size();i++){
      if (objects[i]->box.center()(axis)<mid)
        left_objects.push_back(objects[i]);
      else
        right_objects.push_back(objects[i]);
    }
    if (left_objects.size()==0){
      left_objects.push_back(right_objects.back());
      right_objects.pop_back();
    } else if(right_objects.size()==0){
      right_objects.push_back(left_objects.back());
      left_objects.pop_back();      
    }
    this->left = std::make_shared<AABBTree>(left_objects,a_depth+1);
    this->right = std::make_shared<AABBTree>(right_objects,a_depth+1);
  }
}

bool AABBTree::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const 
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  bool hit_box = ray_intersect_box(ray,this->box,min_t,max_t);
  if (hit_box){
    std::shared_ptr<Object> lde,rde;
    double lt,rt;
    bool l_intersect = left && left->ray_intersect(ray,min_t,max_t,lt,lde);
    bool r_intersect = right && right->ray_intersect(ray,min_t,max_t,rt,rde);

    if (!lde && l_intersect)
      lde = left;
    if (!rde && r_intersect)
      rde = right;
    t = std::numeric_limits<double>::infinity();
    if (l_intersect){
      t = lt;
      descendant = lde;
    }
    if (r_intersect && rt<t){
      t = rt;
      descendant = rde;
    }
    return (l_intersect || r_intersect);
  }
  return false;
  ////////////////////////////////////////////////////////////////////////////
}