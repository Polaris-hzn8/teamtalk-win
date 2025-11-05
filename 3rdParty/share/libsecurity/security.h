
/*
 Reviser: Polaris_hzn8
 Email: lch2022fox@163.com
 Github: https://github.com/Polaris-hzn8
 brief: IM消息加解密
*/

#ifndef __SECURITY_H__
#define __SECURITY_H__

#ifdef __cplusplus
extern "C" {
#endif
    int EncryptMsg(const char* pInData, uint32_t nInLen, char** pOutData, uint32_t& nOutLen);
    int DecryptMsg(const char* pInData, uint32_t nInLen, char** pOutData, uint32_t& nOutLen);
    int EncryptPass(const char* pInData, uint32_t nInLen, char** pOutData, uint32_t& nOutLen);
    void Free(char* pOutData);
#ifdef __cplusplus
}
#endif

#endif
