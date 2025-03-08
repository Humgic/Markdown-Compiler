#ifndef MARKDOWN_PARSER_PARSER_H
#define MARKDOWN_PARSER_PARSER_H

#include "core/document.h"
#include "core/node.h"
#include <string>
#include <memory>

namespace markdown {
namespace parser {

// Markdown解析器
class Parser {
public:
    Parser();
    std::unique_ptr<core::Document> parse(const std::string& markdown);

private:
    std::unique_ptr<core::Document> document_;
    
    // 解析方法
    void parseBlocks(const std::string& markdown);
    void parseHeading(const std::string& line, size_t pos);
    void parseParagraph(const std::string& text);
    void parseInline(const std::string& text, core::Node* parent);
    void parseMath(const std::string& text, core::Node* parent);
    void parseChem(const std::string& text, core::Node* parent);
    void parseTable(const std::string& text);
    
    // 辅助方法
    bool isHeadingLine(const std::string& line, size_t& level);
    bool isEmptyLine(const std::string& line);
    bool isTableLine(const std::string& line);
};

} // namespace parser
} // namespace markdown

#endif // MARKDOWN_PARSER_PARSER_H 