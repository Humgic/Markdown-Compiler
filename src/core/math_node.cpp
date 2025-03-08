#include "core/math_node.h"

namespace markdown {
namespace core {

MathNode::MathNode(NodeType type, const std::string& content) 
    : Node(type), content_(content) {}

const std::string& MathNode::content() const {
    return content_;
}

MathInline::MathInline(const std::string& content) 
    : MathNode(NodeType::MathInline, content) {}

MathBlock::MathBlock(const std::string& content) 
    : MathNode(NodeType::MathBlock, content) {}

MathBlockAlign::MathBlockAlign(const std::string& content) 
    : MathNode(NodeType::MathBlockAlign, content) {}

} // namespace core
} // namespace markdown
