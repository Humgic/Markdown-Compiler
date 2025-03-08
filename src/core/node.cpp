#include "core/node.h"

namespace markdown {
namespace core {

Node::Node(NodeType type) : type_(type) {}

NodeType Node::type() const {
    return type_;
}

void Node::addChild(std::unique_ptr<Node> child) {
    children_.push_back(std::move(child));
}

const std::vector<std::unique_ptr<Node>>& Node::children() const {
    return children_;
}

std::vector<std::unique_ptr<Node>>& Node::children() {
    return children_;
}

} // namespace core
} // namespace markdown 