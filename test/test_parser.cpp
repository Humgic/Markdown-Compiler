#include "markdown.h"
#include <cassert>
#include <iostream>
#include <string>

void testHeadingParsing() {
    markdown::Parser parser;
    
    // 测试标题解析
    auto doc = parser.parse("# 一级标题\n## 二级标题\n### 三级标题");
    
    assert(doc->children().size() == 3);
    assert(doc->children()[0]->type() == markdown::NodeType::Heading);
    assert(doc->children()[1]->type() == markdown::NodeType::Heading);
    assert(doc->children()[2]->type() == markdown::NodeType::Heading);
    
    auto heading1 = static_cast<markdown::Heading*>(doc->children()[0].get());
    auto heading2 = static_cast<markdown::Heading*>(doc->children()[1].get());
    auto heading3 = static_cast<markdown::Heading*>(doc->children()[2].get());
    
    assert(heading1->level() == 1);
    assert(heading2->level() == 2);
    assert(heading3->level() == 3);
    
    std::cout << "标题解析测试通过" << std::endl;
}

void testMathParsing() {
    markdown::Parser parser;
    
    // 测试数学公式解析
    auto doc = parser.parse("行内公式: $E=mc^2$\n\n$$\nE = mc^2\n$$");
    
    assert(doc->children().size() == 2);
    assert(doc->children()[0]->type() == markdown::NodeType::Paragraph);
    assert(doc->children()[1]->type() == markdown::NodeType::MathBlock);
    
    auto paragraph = doc->children()[0].get();
    assert(paragraph->children().size() == 2); // 文本 + 行内公式
    assert(paragraph->children()[1]->type() == markdown::NodeType::MathInline);
    
    auto mathInline = static_cast<markdown::MathInline*>(paragraph->children()[1].get());
    auto mathBlock = static_cast<markdown::MathBlock*>(doc->children()[1].get());
    
    assert(mathInline->content() == "E=mc^2");
    assert(mathBlock->content() == "E = mc^2\n");
    
    std::cout << "数学公式解析测试通过" << std::endl;
}

void testMathBlockAlignParsing() {
    markdown::Parser parser;
    
    // 测试等号对齐数学公式解析
    auto doc = parser.parse("$$$\na &= b + c\\\\\nd &= e * f\n$$$");
    
    assert(doc->children().size() == 1);
    assert(doc->children()[0]->type() == markdown::NodeType::MathBlockAlign);
    
    auto mathBlockAlign = static_cast<markdown::MathBlockAlign*>(doc->children()[0].get());
    assert(mathBlockAlign->content() == "a &= b + c\\\\\nd &= e * f\n");
    
    std::cout << "等号对齐数学公式解析测试通过" << std::endl;
}

void testTableParsing() {
    markdown::Parser parser;
    
    // 测试表格解析
    auto doc = parser.parse("| 表头1 | 表头2 | 表头3 |\n| --- | --- | --- |\n| 单元格1 | 单元格2 | 单元格3 |\n| 单元格4 | 单元格5 | 单元格6 |");
    
    assert(doc->children().size() == 1);
    assert(doc->children()[0]->type() == markdown::NodeType::Table);
    
    auto table = static_cast<markdown::Table*>(doc->children()[0].get());
    assert(table->header() != nullptr);
    assert(table->children().size() == 2); // 两行数据
    
    auto headerRow = table->header().get();
    assert(headerRow->children().size() == 3); // 三列
    
    auto dataRow1 = table->children()[0].get();
    auto dataRow2 = table->children()[1].get();
    assert(dataRow1->children().size() == 3);
    assert(dataRow2->children().size() == 3);
    
    std::cout << "表格解析测试通过" << std::endl;
}

int main() {
    try {
        testHeadingParsing();
        testMathParsing();
        testMathBlockAlignParsing();
        testTableParsing();
        
        std::cout << "所有测试通过!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "测试失败: " << e.what() << std::endl;
        return 1;
    }
} 