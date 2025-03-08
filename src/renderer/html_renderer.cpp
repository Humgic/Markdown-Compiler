#include "renderer/html_renderer.h"
#include "utils/string_utils.h"
#include <sstream>
#include <functional>

namespace markdown {
namespace renderer {

HtmlRenderer::HtmlRenderer() {
    // 初始化渲染器映射
    renderers_[core::NodeType::Document] = [this](const core::Node* node) {
        return renderNode(node);
    };
    
    renderers_[core::NodeType::Heading] = [this](const core::Node* node) {
        return renderHeading(static_cast<const core::Heading*>(node));
    };
    
    renderers_[core::NodeType::Paragraph] = [this](const core::Node* node) {
        std::stringstream ss;
        ss << "<p>";
        for (const auto& child : node->children()) {
            ss << renderNode(child.get());
        }
        ss << "</p>";
        return ss.str();
    };
    
    renderers_[core::NodeType::Text] = [this](const core::Node* node) {
        return renderText(static_cast<const core::Text*>(node));
    };
    
    renderers_[core::NodeType::MathInline] = [this](const core::Node* node) {
        return renderMathInline(static_cast<const core::MathInline*>(node));
    };
    
    renderers_[core::NodeType::MathBlock] = [this](const core::Node* node) {
        return renderMathBlock(static_cast<const core::MathBlock*>(node));
    };
    
    renderers_[core::NodeType::MathBlockAlign] = [this](const core::Node* node) {
        return renderMathBlockAlign(static_cast<const core::MathBlockAlign*>(node));
    };
    
    renderers_[core::NodeType::ChemInline] = [this](const core::Node* node) {
        return renderChemInline(static_cast<const core::ChemInline*>(node));
    };
    
    renderers_[core::NodeType::ChemBlock] = [this](const core::Node* node) {
        return renderChemBlock(static_cast<const core::ChemBlock*>(node));
    };
    
    renderers_[core::NodeType::Table] = [this](const core::Node* node) {
        return renderTable(static_cast<const core::Table*>(node));
    };
    
    renderers_[core::NodeType::TableRow] = [this](const core::Node* node) {
        std::stringstream ss;
        ss << "<tr>";
        for (const auto& child : node->children()) {
            ss << renderNode(child.get());
        }
        ss << "</tr>";
        return ss.str();
    };
    
    renderers_[core::NodeType::TableCell] = [this](const core::Node* node) {
        std::stringstream ss;
        ss << "<td>";
        for (const auto& child : node->children()) {
            ss << renderNode(child.get());
        }
        ss << "</td>";
        return ss.str();
    };
}

std::string HtmlRenderer::render(const core::Document& document) {
    std::stringstream ss;
    
    // 添加HTML头部，专门针对WebKit优化
    ss << "<!DOCTYPE html>\n"
       << "<html>\n"
       << "<head>\n"
       << "    <meta charset=\"UTF-8\">\n"
       << "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no\">\n"
       << "    <meta name=\"apple-mobile-web-app-capable\" content=\"yes\">\n"
       << "    <meta name=\"apple-mobile-web-app-status-bar-style\" content=\"black-translucent\">\n"
       << "    <title>Markdown Document</title>\n"
       << "    <style>\n"
       << "        /* WebKit特定样式 */\n"
       << "        body { font-family: -apple-system, BlinkMacSystemFont, 'Helvetica Neue', sans-serif; line-height: 1.6; padding: 20px; max-width: 800px; margin: 0 auto; -webkit-font-smoothing: antialiased; }\n"
       << "        table { border-collapse: collapse; width: 100%; margin: 20px 0; }\n"
       << "        th, td { border: 1px solid #ddd; padding: 8px; text-align: left; }\n"
       << "        th { background-color: #f2f2f2; }\n"
       << "        .math-inline { font-style: italic; }\n"
       << "        .math-block { display: block; margin: 1em 0; text-align: center; }\n"
       << "        .math-block-align { display: block; margin: 1em 0; }\n"
       << "        .math-block-align .equation { margin-right: 3em; text-align: right; }\n"
       << "        .chem-inline { display: inline-block; min-height: 100px; min-width: 150px; vertical-align: middle; }\n"
       << "        .chem-block { display: block; margin: 1em auto; min-height: 300px; width: 100%; }\n"
       << "        .ketcher-container { width: 100%; height: 100%; }\n"
       << "    </style>\n"
       << "    <!-- MathJax 数学公式渲染器 -->\n"
       << "    <script src=\"https://cdn.jsdelivr.net/npm/mathjax@3/es5/tex-mml-chtml.js\"></script>\n"
       << "    <!-- Ketcher 化学式渲染器 -->\n"
       << "    <script src=\"https://unpkg.com/ketcher-standalone@2.5.1/dist/ketcher.js\"></script>\n"
       << "    <script>\n"
       << "        // WebKit特定的初始化代码\n"
       << "        window.onload = function() {\n"
       << "            // 确保Ketcher已加载\n"
       << "            if (typeof ketcher === 'undefined') {\n"
       << "                console.error('Ketcher library not loaded');\n"
       << "                return;\n"
       << "            }\n"
       << "            \n"
       << "            // 渲染所有化学式\n"
       << "            setTimeout(function() {\n"
       << "                var elements = document.querySelectorAll('.chem-inline, .chem-block');\n"
       << "                for (var i = 0; i < elements.length; i++) {\n"
       << "                    (function(element) {\n"
       << "                        var chemContent = element.getAttribute('data-chem');\n"
       << "                        if (chemContent) {\n"
       << "                            try {\n"
       << "                                // 创建渲染容器\n"
       << "                                var container = document.createElement('div');\n"
       << "                                container.className = 'ketcher-container';\n"
       << "                                element.appendChild(container);\n"
       << "                                \n"
       << "                                // 渲染化学式\n"
       << "                                ketcher.run(container, { staticMode: true })\n"
       << "                                    .then(function(ketcherInstance) {\n"
       << "                                        ketcherInstance.setMolecule(chemContent);\n"
       << "                                    })\n"
       << "                                    .catch(function(error) {\n"
       << "                                        console.error('Failed to render chemical formula:', error);\n"
       << "                                        element.textContent = chemContent;\n"
       << "                                    });\n"
       << "                            } catch (e) {\n"
       << "                                console.error('Failed to render chemical formula:', e);\n"
       << "                                element.textContent = chemContent;\n"
       << "                            }\n"
       << "                        }\n"
       << "                    })(elements[i]);\n"
       << "                }\n"
       << "            }, 300); // 延迟300毫秒，确保页面完全加载\n"
       << "        };\n"
       << "    </script>\n"
       << "</head>\n"
       << "<body>\n";
    
    // 渲染文档内容
    for (const auto& child : document.children()) {
        ss << renderNode(child.get()) << "\n";
    }
    
    // 添加HTML尾部
    ss << "</body>\n"
       << "</html>";
    
    return ss.str();
}

std::string HtmlRenderer::renderNode(const core::Node* node) {
    auto it = renderers_.find(node->type());
    if (it != renderers_.end()) {
        return it->second(node);
    }
    
    // 默认渲染子节点
    std::stringstream ss;
    for (const auto& child : node->children()) {
        ss << renderNode(child.get());
    }
    return ss.str();
}

std::string HtmlRenderer::renderHeading(const core::Heading* heading) {
    std::stringstream ss;
    int level = heading->level();
    if (level > 6) level = 6; // HTML只支持h1-h6
    
    ss << "<h" << level << ">";
    for (const auto& child : heading->children()) {
        ss << renderNode(child.get());
    }
    ss << "</h" << level << ">";
    
    return ss.str();
}

std::string HtmlRenderer::renderText(const core::Text* text) {
    return utils::escapeHtml(text->content());
}

std::string HtmlRenderer::renderMathInline(const core::MathInline* math) {
    return "<span class=\"math-inline\">\\(" + math->content() + "\\)</span>";
}

std::string HtmlRenderer::renderMathBlock(const core::MathBlock* math) {
    return "<div class=\"math-block\">\\[" + math->content() + "\\]</div>";
}

std::string HtmlRenderer::renderMathBlockAlign(const core::MathBlockAlign* math) {
    return "<div class=\"math-block-align\">\\begin{align}" + math->content() + "\\end{align}</div>";
}

std::string HtmlRenderer::renderChemInline(const core::ChemInline* chem) {
    std::string escapedContent = utils::escapeHtml(chem->content());
    return "<span class=\"chem-inline\" data-chem=\"" + escapedContent + "\"></span>";
}

std::string HtmlRenderer::renderChemBlock(const core::ChemBlock* chem) {
    std::string escapedContent = utils::escapeHtml(chem->content());
    return "<div class=\"chem-block\" data-chem=\"" + escapedContent + "\"></div>";
}

std::string HtmlRenderer::renderTable(const core::Table* table) {
    std::stringstream ss;
    ss << "<table>";
    
    // 渲染表头
    if (table->header()) {
        ss << "<thead>";
        std::string headerHtml = renderNode(table->header().get());
        // 将 <td> 替换为 <th>
        headerHtml = utils::replaceAll(headerHtml, "<td>", "<th>");
        headerHtml = utils::replaceAll(headerHtml, "</td>", "</th>");
        ss << headerHtml;
        ss << "</thead>";
    }
    
    // 渲染表格主体
    ss << "<tbody>";
    for (const auto& child : table->children()) {
        ss << renderNode(child.get());
    }
    ss << "</tbody>";
    
    ss << "</table>";
    return ss.str();
}

} // namespace renderer
} // namespace markdown 