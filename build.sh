#!/bin/bash

# 创建目录结构
mkdir -p build/bin

# 编译主程序
g++ -std=c++17 -I./include \
    src/core/*.cpp \
    src/utils/*.cpp \
    src/parser/*.cpp \
    src/renderer/*.cpp \
    src/app/main.cpp \
    -o build/bin/markdown_compiler

# 编译测试程序
g++ -std=c++17 -I./include \
    src/core/*.cpp \
    src/utils/*.cpp \
    src/parser/*.cpp \
    src/renderer/*.cpp \
    test/test_parser.cpp \
    -o build/bin/test_parser

echo "构建完成！"
echo "可执行文件位于 build/bin/markdown_compiler"
echo "测试程序位于 build/bin/test_parser" 