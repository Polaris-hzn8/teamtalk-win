#ifndef UIUSERLIST_92BF7D1E_3298_41A6_93EF_14865AE0DBCC_H__
#define UIUSERLIST_92BF7D1E_3298_41A6_93EF_14865AE0DBCC_H__

#include <global_define.h>
#include <modules/Session/UI/UIIMList.h>
class SessionListItemInfo : public IMListItemInfo {
 public:
  UInt32 Time;
};

class CUIRecentSessionList : public UIIMList {
 public:
  CUIRecentSessionList(CPaintManagerUI& paint_manager);

  Node* AddNode(const SessionListItemInfo& item, Node* parent = NULL, int index = 0);

  BOOL AddNode(const std::string& sId);
  BOOL UpdateItemConentBySId(IN const std::string& sId);    // 更新会话数据，如消息内容，最新时间
  BOOL UpdateItemInfo(IN const SessionListItemInfo& item);  // 更新会话信息，头像等
  void ClearItemMsgCount(IN const std::string& sId);        // 清空显示的未读条数
  void sort();
};

#endif  // UIUSERLIST_92BF7D1E_3298_41A6_93EF_14865AE0DBCC_H__
