
#ifndef LISTCREATFROM_975EBA89_D5AE_43AC_BB2E_F682E2292925_H__
#define LISTCREATFROM_975EBA89_D5AE_43AC_BB2E_F682E2292925_H__

#include <modules/Session/UI/UIIMList.h>

class ListCreatFrom : public UIIMList {
 public:
  Node* AddNode(const IMListItemInfo& item, Node* parent = NULL, int index = 0);
};

#endif  // LISTCREATFROM_975EBA89_D5AE_43AC_BB2E_F682E2292925_H__
