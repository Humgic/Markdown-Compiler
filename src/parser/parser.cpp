#include "parser/parser.h"
#include "core/document.h"
#include "core/heading.h"
#include "core/text.h"
#include "core/math_node.h"
#include "core/chem_node.h"
#include "core/table.h"
#include "utils/string_utils.h"
#include <sstream>
#include <regex>
#include <iostream>
#include <cstring>

namespace markdown {
namespace parser {

// 定义¥符号的UTF-8编码
const char* const YEN_SYMBOL = "\xC2\xA5"; // UTF-8编码的¥符号
const char* const YEN_SYMBOL_DOUBLE = "\xC2\xA5\xC2\xA5"; // 两个连续的¥符号

Parser::Parser() {}

std::unique_ptr<core::Document> Parser::parse(const std::string& markdown) {
    document_ = std::make_unique<core::Document>();
    parseBlocks(markdown);
    return std::move(document_);
}

void Parser::parseBlocks(const std::string& markdown) {
    std::vector<std::string> lines = utils::splitLines(markdown);
    
    size_t i = 0;
    while (i < lines.size()) {
        const std::string& line = lines[i];
        
        // 检查是否为空行
        if (isEmptyLine(line)) {
            i++;
            continue;
        }
        
        // 检查是否为标题
        size_t level;
        if (isHeadingLine(line, level)) {
            parseHeading(line, level);
            i++;
            continue;
        }
        
        // 检查是否为表格
        if (isTableLine(line) && i + 1 < lines.size() && 
            lines[i + 1].find('|') != std::string::npos && 
            lines[i + 1].find('-') != std::string::npos) {
            
            // 收集表格的所有行
            std::string tableText = line + "\n" + lines[i + 1];
            i += 2;
            
            while (i < lines.size() && isTableLine(lines[i])) {
                tableText += "\n" + lines[i];
                i++;
            }
            
            parseTable(tableText);
            continue;
        }
        
        // 检查是否为行间化学式
        if (line.find(YEN_SYMBOL_DOUBLE) == 0) {
            std::string chemContent;
            i++;
            
            while (i < lines.size() && lines[i].find(YEN_SYMBOL_DOUBLE) != 0) {
                chemContent += lines[i] + "\n";
                i++;
            }
            
            if (i < lines.size()) { // 找到了结束标记
                auto chemNode = std::make_unique<core::ChemBlock>(chemContent);
                document_->addChild(std::move(chemNode));
                i++; // 跳过结束标记
            }
            continue;
        }
        
        // 检查是否为等号对齐数学公式块（先检查这个，因为它的标记更长）
        if (line.find("$$$") == 0) {
            std::string mathContent;
            i++;
            
            while (i < lines.size() && lines[i].find("$$$") != 0) {
                mathContent += lines[i] + "\n";
                i++;
            }
            
            if (i < lines.size()) { // 找到了结束标记
                auto mathNode = std::make_unique<core::MathBlockAlign>(mathContent);
                document_->addChild(std::move(mathNode));
                i++; // 跳过结束标记
            }
            continue;
        }
        
        // 检查是否为数学公式块
        if (line.find("$$") == 0) {
            std::string mathContent;
            i++;
            
            while (i < lines.size() && lines[i].find("$$") != 0) {
                mathContent += lines[i] + "\n";
                i++;
            }
            
            if (i < lines.size()) { // 找到了结束标记
                auto mathNode = std::make_unique<core::MathBlock>(mathContent);
                document_->addChild(std::move(mathNode));
                i++; // 跳过结束标记
            }
            continue;
        }
        
        // 默认为段落
        std::string paragraphText = line;
        i++;
        
        while (i < lines.size() && !isEmptyLine(lines[i]) && 
               !isHeadingLine(lines[i], level) && !isTableLine(lines[i]) &&
               lines[i].find("$$") != 0 && lines[i].find("$$$") != 0 && 
               lines[i].find(YEN_SYMBOL_DOUBLE) != 0) {
            paragraphText += "\n" + lines[i];
            i++;
        }
        
        parseParagraph(paragraphText);
    }
}

void Parser::parseHeading(const std::string& line, size_t level) {
    std::string content = line.substr(level + 1); // 跳过 "# " 部分
    content = utils::trim(content);
    
    auto heading = std::make_unique<core::Heading>(level);
    parseInline(content, heading.get());
    document_->addChild(std::move(heading));
}

void Parser::parseParagraph(const std::string& text) {
    auto paragraph = std::make_unique<core::Node>(core::NodeType::Paragraph);
    parseInline(text, paragraph.get());
    document_->addChild(std::move(paragraph));
}

void Parser::parseInline(const std::string& text, core::Node* parent) {
    // 首先处理化学式
    parseChem(text, parent);
    
    // 如果没有化学式，则处理数学公式
    if (parent->children().empty()) {
        parseMath(text, parent);
    }
    
    // 如果没有数学公式和化学式，则作为普通文本处理
    if (parent->children().empty()) {
        auto textNode = std::make_unique<core::Text>(text);
        parent->addChild(std::move(textNode));
    }
}

void Parser::parseMath(const std::string& text, core::Node* parent) {
    std::string remaining = text;
    size_t pos = 0;
    
    while ((pos = remaining.find('$', pos)) != std::string::npos) {
        // 添加前面的文本
        if (pos > 0) {
            auto textNode = std::make_unique<core::Text>(remaining.substr(0, pos));
            parent->addChild(std::move(textNode));
        }
        
        // 检查是否为行内公式
        size_t endPos = remaining.find('$', pos + 1);
        if (endPos != std::string::npos) {
            std::string mathContent = remaining.substr(pos + 1, endPos - pos - 1);
            auto mathNode = std::make_unique<core::MathInline>(mathContent);
            parent->addChild(std::move(mathNode));
            
            remaining = remaining.substr(endPos + 1);
            pos = 0;
        } else {
            // 没有找到结束的 $，将 $ 作为普通字符处理
            auto textNode = std::make_unique<core::Text>(remaining.substr(pos, 1));
            parent->addChild(std::move(textNode));
            remaining = remaining.substr(pos + 1);
            pos = 0;
        }
    }
    
    // 添加剩余的文本
    if (!remaining.empty()) {
        auto textNode = std::make_unique<core::Text>(remaining);
        parent->addChild(std::move(textNode));
    }
}

void Parser::parseChem(const std::string& text, core::Node* parent) {
    std::string remaining = text;
    size_t pos = 0;
    
    while ((pos = remaining.find(YEN_SYMBOL, pos)) != std::string::npos) {
        // 添加前面的文本
        if (pos > 0) {
            auto textNode = std::make_unique<core::Text>(remaining.substr(0, pos));
            parent->addChild(std::move(textNode));
        }
        
        // 检查是否为行内化学式
        size_t endPos = remaining.find(YEN_SYMBOL, pos + strlen(YEN_SYMBOL));
        if (endPos != std::string::npos) {
            std::string chemContent = remaining.substr(pos + strlen(YEN_SYMBOL), endPos - pos - strlen(YEN_SYMBOL));
            auto chemNode = std::make_unique<core::ChemInline>(chemContent);
            parent->addChild(std::move(chemNode));
            
            remaining = remaining.substr(endPos + strlen(YEN_SYMBOL));
            pos = 0;
        } else {
            // 没有找到结束的 ¥，将 ¥ 作为普通字符处理
            auto textNode = std::make_unique<core::Text>(remaining.substr(pos, strlen(YEN_SYMBOL)));
            parent->addChild(std::move(textNode));
            remaining = remaining.substr(pos + strlen(YEN_SYMBOL));
            pos = 0;
        }
    }
    
    // 如果有化学式，不要添加剩余的文本，让数学公式解析器处理
    if (parent->children().empty() && !remaining.empty()) {
        return;
    }
    
    // 如果已经解析了化学式，添加剩余的文本
    if (!parent->children().empty() && !remaining.empty()) {
        auto textNode = std::make_unique<core::Text>(remaining);
        parent->addChild(std::move(textNode));
    }
}

void Parser::parseTable(const std::string& text) {
    std::vector<std::string> lines = utils::splitLines(text);
    if (lines.size() < 2) return; // 至少需要表头和分隔行
    
    auto table = std::make_unique<core::Table>();
    
    // 解析表头
    std::string headerLine = lines[0];
    auto headerRow = std::make_unique<core::Node>(core::NodeType::TableRow);
    
    std::vector<std::string> headerCells;
    size_t start = headerLine.find('|');
    if (start == 0) start = 1; // 跳过开头的 |
    
    size_t end = headerLine.find('|', start);
    while (end != std::string::npos) {
        std::string cellContent = utils::trim(headerLine.substr(start, end - start));
        auto cell = std::make_unique<core::Node>(core::NodeType::TableCell);
        parseInline(cellContent, cell.get());
        headerRow->addChild(std::move(cell));
        
        start = end + 1;
        end = headerLine.find('|', start);
    }
    
    // 处理最后一个单元格（如果有）
    if (start < headerLine.size()) {
        std::string cellContent = utils::trim(headerLine.substr(start));
        if (!cellContent.empty() && cellContent.back() == '|') {
            cellContent = cellContent.substr(0, cellContent.size() - 1);
        }
        cellContent = utils::trim(cellContent);
        
        if (!cellContent.empty()) {
            auto cell = std::make_unique<core::Node>(core::NodeType::TableCell);
            parseInline(cellContent, cell.get());
            headerRow->addChild(std::move(cell));
        }
    }
    
    table->setHeader(std::move(headerRow));
    
    // 跳过分隔行（第二行）
    
    // 解析数据行
    for (size_t i = 2; i < lines.size(); i++) {
        std::string dataLine = lines[i];
        auto dataRow = std::make_unique<core::Node>(core::NodeType::TableRow);
        
        start = dataLine.find('|');
        if (start == 0) start = 1; // 跳过开头的 |
        
        end = dataLine.find('|', start);
        while (end != std::string::npos) {
            std::string cellContent = utils::trim(dataLine.substr(start, end - start));
            auto cell = std::make_unique<core::Node>(core::NodeType::TableCell);
            parseInline(cellContent, cell.get());
            dataRow->addChild(std::move(cell));
            
            start = end + 1;
            end = dataLine.find('|', start);
        }
        
        // 处理最后一个单元格（如果有）
        if (start < dataLine.size()) {
            std::string cellContent = utils::trim(dataLine.substr(start));
            if (!cellContent.empty() && cellContent.back() == '|') {
                cellContent = cellContent.substr(0, cellContent.size() - 1);
            }
            cellContent = utils::trim(cellContent);
            
            if (!cellContent.empty()) {
                auto cell = std::make_unique<core::Node>(core::NodeType::TableCell);
                parseInline(cellContent, cell.get());
                dataRow->addChild(std::move(cell));
            }
        }
        
        table->addChild(std::move(dataRow));
    }
    
    document_->addChild(std::move(table));
}

bool Parser::isHeadingLine(const std::string& line, size_t& level) {
    level = 0;
    while (level < line.size() && line[level] == '#') {
        level++;
    }
    
    return level > 0 && level < line.size() && line[level] == ' ';
}

bool Parser::isEmptyLine(const std::string& line) {
    return utils::trim(line).empty();
}

bool Parser::isTableLine(const std::string& line) {
    return line.find('|') != std::string::npos;
}

} // namespace parser
} // namespace markdown 