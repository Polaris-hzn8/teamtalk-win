
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief:
*/

#ifndef _SUBJECT_H_
#define _SUBJECT_H_

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

#endif// _SUBJECT_H_
