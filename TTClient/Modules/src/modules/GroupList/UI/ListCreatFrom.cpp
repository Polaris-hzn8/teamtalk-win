
#include "stdafx.h"
#include <modules/GroupList/UI/ListCreatFrom.h>

Node* ListCreatFrom::AddNode(const IMListItemInfo& item, Node* parent /*= NULL*/, int index /*= 0*/) {
  return __super::AddNode(item, parent, index);
}
