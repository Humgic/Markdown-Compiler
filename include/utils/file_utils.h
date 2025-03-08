#ifndef MARKDOWN_UTILS_FILE_UTILS_H
#define MARKDOWN_UTILS_FILE_UTILS_H

#include <string>

namespace markdown {
namespace utils {

// 读取文件内容
std::string readFile(const std::string& filename);

// 写入文件内容
void writeFile(const std::string& filename, const std::string& content);

} // namespace utils
} // namespace markdown

#endif // MARKDOWN_UTILS_FILE_UTILS_H 