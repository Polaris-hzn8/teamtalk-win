
#ifndef SEARCHLAYOUT_444A5D88_D118_4093_8D80_C63672830D2D_H__
#define SEARCHLAYOUT_444A5D88_D118_4093_8D80_C63672830D2D_H__

#include <string>
#include <DuiLib/UIlib.h>

using namespace DuiLib;

class CGroupsTreelistUI;
class SearchLayout :public CVerticalLayoutUI, public INotifyUI
{
public:
    SearchLayout();
    ~SearchLayout();
public:
	virtual LPVOID GetInterface(LPCTSTR pstrName);
	virtual LPCTSTR GetClass() const;

	virtual void DoInit();
	virtual void Notify(TNotifyUI& msg);
private:
	void _updateSearchResultList(IN const std::vector<std::string>& nameList,int IdType);
	void _updateSearchResultListForDepartMent(IN const CString strSearch);
private:
	CButtonUI*	m_btnSearch;
	CButtonUI*	m_btnCancel;
	CEditUI*	m_edit;
	CControlUI*	m_layoutSearchResult;
	CGroupsTreelistUI*	m_SearchResultList;
};

#endif// SEARCHLAYOUT_444A5D88_D118_4093_8D80_C63672830D2D_H__
