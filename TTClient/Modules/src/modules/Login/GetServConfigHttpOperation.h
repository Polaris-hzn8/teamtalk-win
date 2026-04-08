
#ifndef PHPCONECTOPERATION_E51819EF_B832_486D_A1D0_B9873C45FC4E_H__
#define PHPCONECTOPERATION_E51819EF_B832_486D_A1D0_B9873C45FC4E_H__

#include <modules/IHttpPoolModule.h>
#include <string>

enum {
  GETSERV_CONFIT_SUCC = 0,
  GETSERV_CONFIT_FAIL,
};

class GetServConfigParam {
 public:
  UInt8 result = GETSERV_CONFIT_FAIL;
};

class GetServConfigHttpOperation : public module::IHttpOperation {
 public:
  GetServConfigHttpOperation(module::IOperationDelegate callback, GetServConfigParam& param);
  virtual ~GetServConfigHttpOperation();

 public:
  virtual void processOpertion();
  virtual void release();

 private:
  GetServConfigParam m_param;
};

#endif  // PHPCONECTOPERATION_E51819EF_B832_486D_A1D0_B9873C45FC4E_H__