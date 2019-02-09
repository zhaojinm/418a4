#include "find_all_intersecting_pairs_using_AABBTrees.h"
#include "box_box_intersect.h"
// Hint: use a list as a queue
#include <list> 
typedef std::pair<std::shared_ptr<AABBTree>, std::shared_ptr<AABBTree>> pair;
typedef std::pair<std::shared_ptr<Object>, std::shared_ptr<Object>> obpair;
void find_all_intersecting_pairs_using_AABBTrees(
  const std::shared_ptr<AABBTree> & rootA,
  const std::shared_ptr<AABBTree> & rootB,
  std::vector<std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> > > & 
    leaf_pairs)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  std::list<pair> pair_list;
  if (box_box_intersect(rootA->box, rootB->box)) {
    pair first_pair (rootA,rootB);
    pair_list.push_back(first_pair);
  }
  while (!pair_list.empty()){
    std::shared_ptr<AABBTree> nodeA = pair_list.front().first;
    std::shared_ptr<AABBTree> nodeB = pair_list.front().second;
    pair_list.pop_front();
    if (nodeA->num_leaves <= 2 && nodeB->num_leaves <= 2){
      obpair p1 (nodeA->left, nodeB->left);
      if (nodeA->left && nodeB->left && box_box_intersect(nodeA->left->box, nodeB->left->box))
        leaf_pairs.push_back(p1);
      obpair p2 (nodeA->left, nodeB->right);
      if (nodeA->left && nodeB->right && box_box_intersect(nodeA->left->box, nodeB->right->box))
        leaf_pairs.push_back(p2);
      obpair p3 (nodeA->right, nodeB->left);
      if (nodeA->right && nodeB->left && box_box_intersect(nodeA->right->box, nodeB->left->box))
        leaf_pairs.push_back(p3);
      obpair p4 (nodeA->right, nodeB->right);
      if (nodeA->right && nodeB->right && box_box_intersect(nodeA->right->box, nodeB->right->box))
        leaf_pairs.push_back(p4);
    }else if (nodeA->num_leaves <= 2){
      pair p1 (std::static_pointer_cast<AABBTree>(nodeA), std::static_pointer_cast<AABBTree>(nodeB->left));
      if (box_box_intersect(nodeA->box, nodeB->left->box))
        pair_list.push_back(p1);
      pair p2 (std::static_pointer_cast<AABBTree>(nodeA), std::static_pointer_cast<AABBTree>(nodeB->right));
      if (box_box_intersect(nodeA->box, nodeB->right->box))
        pair_list.push_back(p2);
    }else if (nodeB->num_leaves <= 2){
      pair p1 (std::static_pointer_cast<AABBTree>(nodeA->left), std::static_pointer_cast<AABBTree>(nodeB));
      if (box_box_intersect(nodeA->left->box, nodeB->box))
        pair_list.push_back(p1);
      pair p2 (std::static_pointer_cast<AABBTree>(nodeA->right), std::static_pointer_cast<AABBTree>(nodeB));
      if (box_box_intersect(nodeA->right->box, nodeB->box))
        pair_list.push_back(p2);
    }else{
      pair p1 (std::static_pointer_cast<AABBTree>(nodeA->left), std::static_pointer_cast<AABBTree>(nodeB->left));
      if (box_box_intersect(nodeA->left->box, nodeB->left->box))
        pair_list.push_back(p1);
      pair p2 (std::static_pointer_cast<AABBTree>(nodeA->left), std::static_pointer_cast<AABBTree>(nodeB->right));
      if (box_box_intersect(nodeA->left->box, nodeB->right->box))
        pair_list.push_back(p2);
      pair p3 (std::static_pointer_cast<AABBTree>(nodeA->right), std::static_pointer_cast<AABBTree>(nodeB->left));
      if (box_box_intersect(nodeA->right->box, nodeB->left->box))
        pair_list.push_back(p3);
      pair p4 (std::static_pointer_cast<AABBTree>(nodeA->right), std::static_pointer_cast<AABBTree>(nodeB->right));
      if (box_box_intersect(nodeA->right->box, nodeB->right->box))
        pair_list.push_back(p4);
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
