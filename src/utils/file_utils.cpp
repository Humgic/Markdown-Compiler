#include "utils/file_utils.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace markdown {
namespace utils {

std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("无法打开文件: " + filename);
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void writeFile(const std::string& filename, const std::string& content) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("无法写入文件: " + filename);
    }
    
    file << content;
}

} // namespace utils
} // namespace markdown 