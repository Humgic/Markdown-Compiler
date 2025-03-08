#ifndef MARKDOWN_UTILS_STRING_UTILS_H
#define MARKDOWN_UTILS_STRING_UTILS_H

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

namespace markdown {
namespace utils {

// 去除字符串两端的空白字符
std::string trim(const std::string& str);

// 分割字符串
std::vector<std::string> split(const std::string& str, const std::string& delimiter);

// 分割字符串为行
std::vector<std::string> splitLines(const std::string& str);

// HTML转义
std::string escapeHtml(const std::string& str);

// 检查字符串是否以指定前缀开始
bool startsWith(const std::string& str, const std::string& prefix);

// 检查字符串是否以指定后缀结束
bool endsWith(const std::string& str, const std::string& suffix);

// 替换字符串中的所有匹配项
std::string replaceAll(const std::string& str, const std::string& from, const std::string& to);

} // namespace utils
} // namespace markdown

#endif // MARKDOWN_UTILS_STRING_UTILS_H 