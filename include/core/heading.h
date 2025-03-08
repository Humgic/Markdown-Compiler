#ifndef MARKDOWN_CORE_HEADING_H
#define MARKDOWN_CORE_HEADING_H

#include "core/node.h"

namespace markdown {
namespace core {

// 标题节点
class Heading : public Node {
public:
    Heading(int level);
    int level() const;
private:
    int level_; // 标题级别 (1-6)
};

} // namespace core
} // namespace markdown

#endif // MARKDOWN_CORE_HEADING_H 