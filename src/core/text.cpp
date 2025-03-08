#include "core/text.h"

namespace markdown {
namespace core {

Text::Text(const std::string& content) : Node(NodeType::Text), content_(content) {}

const std::string& Text::content() const {
    return content_;
}

} // namespace core
} // namespace markdown
