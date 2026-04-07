
#ifndef UIGROUPSTREELIST_A6A09709_9687_4B3D_8924_25CA7CBC4A8F_H__
#define UIGROUPSTREELIST_A6A09709_9687_4B3D_8924_25CA7CBC4A8F_H__

#include <modules/Session/UI/UIIMList.h>

const CDuiString MY_DISCUSSGROUP_ITEMID = _T("myDiscussGroup_id");
const CDuiString MY_GROUP_ITEMID = _T("mygroup_id");

class GroupsListItemInfo final :public IMListItemInfo
{

};

class CGroupsTreelistUI final: public UIIMList
{
public:
	
	CGroupsTreelistUI(CPaintManagerUI& paint_manager);

	Node* AddNode(const GroupsListItemInfo& item, Node* parent = NULL);//增加群
	Node* UpdateNode(const GroupsListItemInfo& groupInfo);//更新群信息
	BOOL UpdateItemBySId(const std::string& sId);
	void ClearItemMsgCount(IN const std::string& sId);//清空显示的未读条数

	BOOL GetFirstChildItemSId(OUT std::string& sId);//找根节点第一个有效节点，返回该sid（用户未设置则返回空）
};

#endif// UIGROUPSTREELIST_a6a09709-9687-4b3d-8924-25ca7cbc4a8f_H__
