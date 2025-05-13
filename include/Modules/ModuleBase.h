
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief:
*/

#ifndef MODULEBASE_A97FF157_CFAF_41B8_B21C_59ED6AA5A8ED_H__
#define MODULEBASE_A97FF157_CFAF_41B8_B21C_59ED6AA5A8ED_H__

#include "GlobalDefine.h"
#include "Modules/ModuleDll.h"
#include "Modules/ModuleObserver.h"

NAMESPACE_BEGIN(module)

class ModuleSubject;
class MODULE_CLASS ModuleBase
{
public:
    ModuleBase();
    ~ModuleBase();
public:
	void addObserver(IN void* pObserObject, IN MKODelegate handle);
	void removeObserver(IN void* pObserObject);
	void asynNotifyObserver(IN const std::string& keyId);
	void asynNotifyObserver(IN const std::string& keyId, IN std::string& mkoString);
	void asynNotifyObserver(IN const std::string& keyId, IN Int32 mkoInt);
	void asynNotifyObserver(IN const std::string& keyId, IN void* pmkoVoid);
	void asynNotifyObserver(IN const std::string& keyId, IN std::shared_ptr<void> pmkoShardVoid);
private:
	ModuleSubject*			m_pModuleSubject;
};

NAMESPACE_END(module)

#endif// MODULEBASE_A97FF157_CFAF_41B8_B21C_59ED6AA5A8ED_H__
