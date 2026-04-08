
#ifndef LISTGROUPMEMBERS_511D645A_CDE2_46B9_9F84_B2D413FFCC54_H__
#define LISTGROUPMEMBERS_511D645A_CDE2_46B9_9F84_B2D413FFCC54_H__

#include <modules/Session/UI/UIIMList.h>

class ListGroupMembers : public UIIMList {
 public:
  ListGroupMembers(CPaintManagerUI& paint_manager);
  Node* AddNode(const IMListItemInfo& item, Node* parent = NULL, int index = 0);
};

#endif  // LISTGROUPMEMBERS_511D645A_CDE2_46B9_9F84_B2D413FFCC54_H__
