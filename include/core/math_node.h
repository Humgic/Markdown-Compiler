#ifndef MARKDOWN_CORE_MATH_NODE_H
#define MARKDOWN_CORE_MATH_NODE_H

#include "core/node.h"
#include <string>

namespace markdown {
namespace core {

// 数学公式节点基类
class MathNode : public Node {
public:
    MathNode(NodeType type, const std::string& content);
    const std::string& content() const;
private:
    std::string content_;
};

// 行内公式节点
class MathInline : public MathNode {
public:
    MathInline(const std::string& content);
};

// 行间公式节点
class MathBlock : public MathNode {
public:
    MathBlock(const std::string& content);
};

// 等号对齐公式节点
class MathBlockAlign : public MathNode {
public:
    MathBlockAlign(const std::string& content);
};

} // namespace core
} // namespace markdown

#endif // MARKDOWN_CORE_MATH_NODE_H 