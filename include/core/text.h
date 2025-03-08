#ifndef MARKDOWN_CORE_TEXT_H
#define MARKDOWN_CORE_TEXT_H

#include "core/node.h"
#include <string>

namespace markdown {
namespace core {

// 文本节点
class Text : public Node {
public:
    Text(const std::string& content);
    const std::string& content() const;
private:
    std::string content_;
};

} // namespace core
} // namespace markdown

#endif // MARKDOWN_CORE_TEXT_H 