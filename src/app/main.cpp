#include "markdown.h"
#include <iostream>
#include <string>

void printUsage(const char* programName) {
    std::cerr << "用法: " << programName << " <输入文件.md> <输出文件.html>" << std::endl;
}

int main(int argc, char* argv[]) {
    // 检查命令行参数
    if (argc != 3) {
        printUsage(argv[0]);
        return 1;
    }
    
    try {
        // 读取输入文件
        std::string inputFilename = argv[1];
        std::string outputFilename = argv[2];
        std::string markdownContent = markdown::utils::readFile(inputFilename);
        
        // 解析Markdown
        markdown::Parser parser;
        auto document = parser.parse(markdownContent);
        
        // 渲染HTML
        markdown::HtmlRenderer renderer;
        std::string htmlContent = renderer.render(*document);
        
        // 写入输出文件
        markdown::utils::writeFile(outputFilename, htmlContent);
        
        std::cout << "成功将 " << inputFilename << " 转换为 " << outputFilename << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "错误: " << e.what() << std::endl;
        return 1;
    }
} 