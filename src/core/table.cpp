#include "core/table.h"

namespace markdown {
namespace core {

Table::Table() : Node(NodeType::Table) {}

void Table::setHeader(std::unique_ptr<Node> header) {
    header_ = std::move(header);
}

const std::unique_ptr<Node>& Table::header() const {
    return header_;
}

} // namespace core
} // namespace markdown
