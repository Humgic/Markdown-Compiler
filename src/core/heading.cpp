#include "core/heading.h"

namespace markdown {
namespace core {

Heading::Heading(int level) : Node(NodeType::Heading), level_(level) {}

int Heading::level() const {
    return level_;
}

} // namespace core
} // namespace markdown
