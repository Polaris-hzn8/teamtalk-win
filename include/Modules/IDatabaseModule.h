
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief: 借助sqlite实现本地数据存储模块 如用户信息等
*/

#ifndef IDATABASEMODULE_086C113C_CEE3_423B_81D1_D771B443A991_H__
#define IDATABASEMODULE_086C113C_CEE3_423B_81D1_D771B443A991_H__

#include <vector>
#include "GlobalDefine.h"
#include "Modules/ModuleDll.h"
#include "Modules/ModuleBase.h"
#include "Modules/ISessionModule.h"
#include "Modules/IUserListModule.h"
#include "Modules/IGroupListModule.h"

class MessageEntity;
class TransferFileEntity;
NAMESPACE_BEGIN(module)
struct ImImageEntity
{
	UInt32				hashcode;		//根据urlPath计算的hash值
	std::string			filename;		//图片本地存储名称
	std::string			urlPath;		//图片url
};

class MODULE_API IDatabaseModule : public module::ModuleBase
{
public:
	// 图片存储相关
	virtual BOOL sqlInsertImImageEntity(const ImImageEntity& entity) = 0;
	virtual BOOL sqlGetImImageEntityByHashcode(UInt32 hashcode,ImImageEntity& entity) = 0;
	virtual BOOL sqlUpdateImImageEntity(UInt32 hashcode, module::ImImageEntity& entity) = 0;

	// 最近联系会话信息
	virtual BOOL sqlGetRecentSessionInfoByGId(IN std::string& sId, OUT module::SessionEntity& sessionInfo) = 0;
	virtual BOOL sqlGetAllRecentSessionInfo(OUT std::vector<module::SessionEntity>& sessionList) = 0;
	virtual BOOL sqlInsertRecentSessionInfoEntity(IN const module::SessionEntity& sessionInfo) = 0;
	virtual BOOL sqlDeleteRecentSessionInfoEntity(IN const std::string& sessionId) = 0;
	virtual BOOL sqlUpdateRecentSessionInfoEntity(IN const module::SessionEntity& sessionInfo) = 0;
	virtual BOOL sqlBatchInsertRecentSessionInfos(IN std::vector<module::SessionEntity>& sessionList) = 0;
	
	// 用户信息相关
	virtual BOOL sqlGetAllUsersInfo(OUT std::vector<module::UserInfoEntity>& userList) = 0;
	virtual BOOL sqlGetUserInfoBySId(IN std::string& sId, OUT module::UserInfoEntity& userInfo) = 0;
	virtual BOOL sqlInsertUserInfoEntity(IN const module::UserInfoEntity& userInfo) = 0;
	virtual BOOL sqlUpdateUserInfoEntity(std::string& sId, IN const module::UserInfoEntity& userInfo) = 0;
	virtual BOOL sqlBatchInsertUserInfos(IN module::UserInfoEntityMap& mapUserInfos) = 0;

	// 部门信息相关
	virtual BOOL sqlGetAllDepartmentInfo(OUT std::vector<module::DepartmentEntity>& departmentList) = 0;
	virtual BOOL sqlGetDepartmentBySId(IN std::string& sId, OUT module::DepartmentEntity& departmentInfo) = 0;
	virtual BOOL sqlInsertDepartmentInfoEntity(IN const module::DepartmentEntity& departmentInfo) = 0;
	virtual BOOL sqlUpdateDepartmentInfoEntity(std::string& sId, IN const module::DepartmentEntity& departmentInfo) = 0;
	virtual BOOL sqlBatchInsertDepartmentInfos(IN module::DepartmentMap& mapDepartmentInfos) = 0;
	
	// 群信息相关
	virtual BOOL sqlGetGroupInfoByGId(IN std::string& gId,OUT module::GroupInfoEntity& groupInfo) = 0;
	virtual BOOL sqlGetAllGroupInfo(OUT std::vector<module::GroupInfoEntity>& groupList) = 0;
	virtual BOOL sqlInsertOrReplaceGroupInfoEntity(IN const module::GroupInfoEntity& groupInfo) = 0;
	virtual BOOL sqlDeleteGroupInfoEntity(IN const std::string& groupId) = 0;
	virtual BOOL sqlUpdateGroupInfoEntity(std::string& sId, IN const module::GroupInfoEntity& groupInfo) = 0;
	virtual BOOL sqlBatchInsertGroupInfos(IN module::GroupInfoMap& mapGroupInfos) = 0;
	
	// 会话消息相关
	virtual BOOL sqlInsertMessage(IN MessageEntity& msg) = 0;
	virtual BOOL sqlBatchInsertMessage(IN std::list<MessageEntity>& msgList) = 0;
	virtual BOOL sqlGetHistoryMessage(IN const std::string& sId, IN const UInt32 msgId, IN UInt32 nMsgCount
									, OUT std::vector<MessageEntity>& msgList) = 0;
	// 文件传输相关
	virtual BOOL sqlInsertFileTransferHistory(IN TransferFileEntity& fileInfo) = 0;
	virtual BOOL sqlGetFileTransferHistory(OUT std::vector<TransferFileEntity>& fileList) = 0;
};

MODULE_API IDatabaseModule* getDatabaseModule();

NAMESPACE_END(module)

#endif// IDATABASEMODULE_086C113C_CEE3_423B_81D1_D771B443A991_H__
