#ifndef MARKDOWN_CORE_TABLE_H
#define MARKDOWN_CORE_TABLE_H

#include "core/node.h"
#include <memory>

namespace markdown {
namespace core {

// 表格节点
class Table : public Node {
public:
    Table();
    void setHeader(std::unique_ptr<Node> header);
    const std::unique_ptr<Node>& header() const;
private:
    std::unique_ptr<Node> header_;
};

} // namespace core
} // namespace markdown

#endif // MARKDOWN_CORE_TABLE_H 