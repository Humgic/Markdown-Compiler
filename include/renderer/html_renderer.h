#ifndef MARKDOWN_RENDERER_HTML_RENDERER_H
#define MARKDOWN_RENDERER_HTML_RENDERER_H

#include "core/document.h"
#include "core/node.h"
#include "core/heading.h"
#include "core/text.h"
#include "core/math_node.h"
#include "core/chem_node.h"
#include "core/table.h"
#include <string>
#include <unordered_map>
#include <functional>

namespace markdown {
namespace renderer {

// HTML渲染器
class HtmlRenderer {
public:
    HtmlRenderer();
    std::string render(const core::Document& document);

private:
    std::string renderNode(const core::Node* node);
    std::string renderHeading(const core::Heading* heading);
    std::string renderText(const core::Text* text);
    std::string renderMathInline(const core::MathInline* math);
    std::string renderMathBlock(const core::MathBlock* math);
    std::string renderMathBlockAlign(const core::MathBlockAlign* math);
    std::string renderChemInline(const core::ChemInline* chem);
    std::string renderChemBlock(const core::ChemBlock* chem);
    std::string renderTable(const core::Table* table);
    
    std::unordered_map<core::NodeType, std::function<std::string(const core::Node*)>> renderers_;
};

} // namespace renderer
} // namespace markdown

#endif // MARKDOWN_RENDERER_HTML_RENDERER_H 