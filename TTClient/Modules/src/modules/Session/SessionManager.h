
#ifndef SESSIONMANAGER_863FBDB8_F00A_4A46_8F57_1AECBC9D277E_H__
#define SESSIONMANAGER_863FBDB8_F00A_4A46_8F57_1AECBC9D277E_H__

#include <global_define.h>
#include <modules/ISessionModule.h>
#include <network/basic/lock.h>

class SessionDialog;
class SessionEntityManager {
 public:
  ~SessionEntityManager();
  static SessionEntityManager* getInstance();

 private:
  SessionEntityManager();

 public:
  module::SessionEntity* getSessionEntityBySId(IN const std::string& sId);
  void setSessionEntity(IN const module::SessionEntity& sessionInfo);
  void getRecentSessionList(OUT std::vector<std::string>& vecRecentSession);
  module::SessionEntity* createSessionEntity(const std::string& sId);
  BOOL removeSessionEntity(const std::string& sId);
  inline void setGlobalUpdatedTime(IN const UInt32 updateTime) { m_globalUpdatedTime = updateTime; }
  inline UInt32 getGlobalUpdateTime() const { return m_globalUpdatedTime; }
  BOOL loadSessionEntityFromDB();

 private:
  UInt8 _getSessionType(IN const std::string& sID);
  void _removeAllSessionEntity();

 private:
  CLock m_lock;
  std::map<std::string, module::SessionEntity*> m_mapSessionEntity;
  std::vector<std::string> m_vecRecentSession;  // 最近联系的ID列表
  UInt32 m_globalUpdatedTime = 0;
};

// 已经打开的会话
class SessionDialogManager {
 public:
  SessionDialog* openSessionDialog(IN const std::string& sId);
  SessionDialog* findSessionDialogBySId(IN const std::string& sId);
  void removeSessionDialogPtr(IN const std::string& sId);
  static SessionDialogManager* getInstance();

 private:
  SessionDialogManager() = default;

 private:
  std::list<SessionDialog*> m_lstSessionDialog;
};

#endif  // SESSIONMANAGER_863FBDB8_F00A_4A46_8F57_1AECBC9D277E_H__
