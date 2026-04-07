
#ifndef UIEAUSERTREELIST_336BA069_7979J_4659_9E6C_0409B5280078_H__
#define UIEAUSERTREELIST_336BA069_7979J_4659_9E6C_0409B5280078_H__

#include <modules/Session/UI/UIIMList.h>

class EAUserTreeListItemInfo :public IMListItemInfo
{

};

class CEAUserTreelistUI final: public UIIMList
{
public:

	CEAUserTreelistUI(CPaintManagerUI& paint_manager);

	Node* AddNode(const EAUserTreeListItemInfo& item, Node* parent = NULL);
	BOOL UpdateItemBySId(const std::string& sId);
	void ClearItemMsgCount(IN const std::string& sId);//清空显示的未读条数
	void sortByOnlineState();
};

#endif// UIEAUSERTREELIST_336BA069_7979J_4659_9E6C_0409B5280078_H__
