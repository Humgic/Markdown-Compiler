#ifndef MARKDOWN_CORE_CHEM_NODE_H
#define MARKDOWN_CORE_CHEM_NODE_H

#include "core/node.h"
#include <string>

namespace markdown {
namespace core {

// 化学式节点基类
class ChemNode : public Node {
public:
    ChemNode(NodeType type, const std::string& content);
    const std::string& content() const;
private:
    std::string content_;
};

// 行内化学式节点
class ChemInline : public ChemNode {
public:
    ChemInline(const std::string& content);
};

// 行间化学式节点
class ChemBlock : public ChemNode {
public:
    ChemBlock(const std::string& content);
};

} // namespace core
} // namespace markdown

#endif // MARKDOWN_CORE_CHEM_NODE_H 