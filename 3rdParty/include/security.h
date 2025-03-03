
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
    
#ifdef __ANDROID__
    jstring Java_com_mogujie_im_security_EncryptMsg(JNIEnv* env, jobject obj, jstring jstr);
    jstring Java_com_mogujie_im_security_DecryptMsg(JNIEnv* env, jobject obj, jstring jstr);
    jstring Java_com_mogujie_im_security_EncryptPass(JNIEnv* env, jobject obj, jstring jstr, jstring jkey);
#else
    int EncryptMsg(const char* pInData, uint32_t nInLen, char** pOutData, uint32_t& nOutLen);
    int DecryptMsg(const char* pInData, uint32_t nInLen, char** pOutData, uint32_t& nOutLen);
    int EncryptPass(const char* pInData, uint32_t nInLen, char** pOutData, uint32_t& nOutLen);
    void Free(char* pOutData);
#endif
    
#ifdef __cplusplus
}
#endif

#endif
