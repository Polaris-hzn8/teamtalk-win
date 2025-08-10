
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief:
*/

#ifndef SUBJECT_4190BD99_2B5F_413C_8E1C_74EFBE2671B9_H__
#define SUBJECT_4190BD99_2B5F_413C_8E1C_74EFBE2671B9_H__

#include <vector>
#include "GlobalDefine.h"
#include "network/Lock.h"
#include "Modules/ModuleObserver.h"

NAMESPACE_BEGIN(module)

class ModuleSubject final
{
public:
    ModuleSubject();
    ~ModuleSubject();
public:
	void addObserver(IN void* pObserObject, IN MKODelegate handle);
	void removeObserver(IN void* pObserObject);
	void asynNotifyObserver(IN const std::string& keyId);
	void asynNotifyObserver(IN const std::string& keyId, IN std::string& mkoString);
	void asynNotifyObserver(IN const std::string& keyId, IN Int32 mkoInt);
	void asynNotifyObserver(IN const std::string& keyId, IN void* pmkoVoid);
	void asynNotifyObserver(IN const std::string& keyId, IN std::shared_ptr<void> pmkoShardVoid);

	void getIObserverHandlersByModuleId(OUT std::vector<MKODelegate>& vecMKOCallbacks);
	BOOL isObserverExist(IN const void* pObserObject);

private:
	void _removeAllObservers();
	void _asynNotifyObserver(IN const std::string& keyId, IN MKOEvent_Impl* pEvent);

private:
	std::vector<ModuleObserverCtx*>	m_vecObservers;
	CLock							m_lockObserver;
};

NAMESPACE_END(module)

#endif// SUBJECT_4190bd99-2b5f-413c-8e1c-74efbe2671b9_H__
