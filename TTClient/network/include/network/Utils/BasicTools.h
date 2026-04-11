
#ifndef _BASIC_TOOLS_H_
#define _BASIC_TOOLS_H_

#include <mutex>
#include <string>
#include <network/ostype.h>

namespace network {

// 时间和延时
uint64_t get_tick_count();
void util_sleep(uint32_t millisecond);

// 文件操作
size_t get_file_size(const char* path);

// 网络IP转换
unsigned int ip2long(const char* ip);
char* long2ip(const unsigned int in);

// 进程相关
void writePid();

// 字符串转换
std::string int2string(uint32_t user_id);
uint32_t string2int(const std::string& value);

// 字符串替换
void replace_mark(std::string& str, std::string& new_value, uint32_t& start_pos);
void replace_mark(std::string& str, uint32_t new_value, uint32_t& start_pos);
char* replaceStr(char* pSrc, char oldChar, char newChar);

/// @brief 将id转换为url（线程安全）
/// @param id 要转换的id
/// @return 转换后的url
std::string idtourl(uint32_t id);

/// @brief 将url转换为id
/// @param url 要转换的url
/// @return 转换后的id
uint32_t urltoid(const char* url);

}  // namespace network

#endif  // _BASIC_TOOLS_H_
