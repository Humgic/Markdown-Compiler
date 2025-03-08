#include "core/chem_node.h"

namespace markdown {
namespace core {

ChemNode::ChemNode(NodeType type, const std::string& content) 
    : Node(type), content_(content) {}

const std::string& ChemNode::content() const {
    return content_;
}

ChemInline::ChemInline(const std::string& content) 
    : ChemNode(NodeType::ChemInline, content) {}

ChemBlock::ChemBlock(const std::string& content) 
    : ChemNode(NodeType::ChemBlock, content) {}

} // namespace core
} // namespace markdown 