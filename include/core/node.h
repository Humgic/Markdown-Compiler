#ifndef MARKDOWN_CORE_NODE_H
#define MARKDOWN_CORE_NODE_H

#include <string>
#include <vector>
#include <memory>

namespace markdown {
namespace core {

// Markdown节点类型
enum class NodeType {
    Document,
    Heading,
    Paragraph,
    Text,
    Bold,
    Italic,
    Code,
    CodeBlock,
    Link,
    Image,
    List,
    ListItem,
    Table,
    TableRow,
    TableCell,
    HorizontalRule,
    MathInline,      // 行内公式 $...$
    MathBlock,       // 边缘自动换行的行间公式 $$...$$
    MathBlockAlign,  // 等号自动换行的行间公式 $$$...$$$ 
    ChemInline,      // 行内化学式 ¥...¥
    ChemBlock        // 行间化学式 ¥¥...¥¥
};

// 基础节点类
class Node {
public:
    Node(NodeType type);
    virtual ~Node() = default;

    NodeType type() const;
    
    void addChild(std::unique_ptr<Node> child);
    
    const std::vector<std::unique_ptr<Node>>& children() const;
    std::vector<std::unique_ptr<Node>>& children();

protected:
    NodeType type_;
    std::vector<std::unique_ptr<Node>> children_;
};

} // namespace core
} // namespace markdown

#endif // MARKDOWN_CORE_NODE_H 