#ifndef MARKDOWN_H
#define MARKDOWN_H

// 核心模块
#include "core/node.h"
#include "core/document.h"
#include "core/heading.h"
#include "core/text.h"
#include "core/math_node.h"
#include "core/table.h"
#include "core/chem_node.h"

// 解析器模块
#include "parser/parser.h"

// 渲染器模块
#include "renderer/html_renderer.h"

// 工具模块
#include "utils/string_utils.h"
#include "utils/file_utils.h"

namespace markdown {

// 使用核心模块的类型
using Document = core::Document;
using Node = core::Node;
using NodeType = core::NodeType;
using Heading = core::Heading;
using Text = core::Text;
using MathNode = core::MathNode;
using MathInline = core::MathInline;
using MathBlock = core::MathBlock;
using MathBlockAlign = core::MathBlockAlign;
using Table = core::Table;
using ChemNode = core::ChemNode;
using ChemInline = core::ChemInline;
using ChemBlock = core::ChemBlock;

// 使用解析器模块的类型
using Parser = parser::Parser;

// 使用渲染器模块的类型
using HtmlRenderer = renderer::HtmlRenderer;

} // namespace markdown

#endif // MARKDOWN_H 