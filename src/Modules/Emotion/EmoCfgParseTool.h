
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief:
*/

#ifndef EMOCFGPARSETOOL_5B1DB11A_DE23_4672_9CC0_A5F7C9F27D6B_H__
#define EMOCFGPARSETOOL_5B1DB11A_DE23_4672_9CC0_A5F7C9F27D6B_H__

#include <list>
#include "GlobalDefine.h"

class  EmoCfgParseTool
{
public:
	EmoCfgParseTool() = default;
	~EmoCfgParseTool() = default;

public:
	CString	   getIDByName(IN LPCTSTR strID);
	CString    getNameByID(IN LPCTSTR str);
	void       getAllNames(OUT std::list<CString>& nameList);

	void	   loadCfgFile(IN LPCTSTR strFilePath);

private:
	std::map<CString, CString> m_mapKey2Value;
};

#endif// EMOCFGPARSETOOL_5B1DB11A_DE23_4672_9CC0_A5F7C9F27D6B_H__
