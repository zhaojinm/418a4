#include "point_AABBTree_squared_distance.h"
#include <queue> // std::priority_queue
#include "point_box_squared_distance.h"
typedef std::pair<double, std::shared_ptr<AABBTree>> pi;
bool point_AABBTree_squared_distance(
    const Eigen::RowVector3d & query,
    const std::shared_ptr<AABBTree> & root,
    const double min_sqrd,
    const double max_sqrd,
    double & sqrd,
    std::shared_ptr<Object> & descendant)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here
  sqrd = std::numeric_limits<double>::infinity();
  std::priority_queue<pi,std::vector<pi>, std::greater<pi>> queue;
  pi pair (point_box_squared_distance(query, root->box), root);
  queue.push(pair);
  while (!queue.empty()){
    pi first_element = queue.top();
    queue.pop();
    double cur_dis = first_element.first;
    std::shared_ptr<AABBTree> cur_tree = first_element.second;
    if (cur_dis<sqrd){
      //not reach terminals
      if (cur_tree->num_leaves>2){
        pi leftp (point_box_squared_distance(query,cur_tree->left->box),std::static_pointer_cast<AABBTree>(cur_tree->left));
        queue.push(leftp);
        pi rightp (point_box_squared_distance(query,cur_tree->right->box),std::static_pointer_cast<AABBTree>(cur_tree->right));
        queue.push(rightp);
      //leaves
      }else{
        double lsqrd,rsqrd;
        std::shared_ptr<Object> ldes,rdes;
        bool l = cur_tree->left && cur_tree->left->point_squared_distance(query, min_sqrd, max_sqrd, lsqrd, ldes);
        bool r = cur_tree->right && cur_tree->right->point_squared_distance(query, min_sqrd, max_sqrd, rsqrd, rdes);
        if (l && lsqrd<sqrd){
          sqrd = lsqrd;
          descendant = cur_tree->left;
        }
        if (r && rsqrd<sqrd){
          sqrd = rsqrd;
          descendant = cur_tree->right;
        }
      }
    }
  }
  return descendant!=NULL;
  ////////////////////////////////////////////////////////////////////////////
}
