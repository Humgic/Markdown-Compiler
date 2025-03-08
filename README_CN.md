# Markdown C++ 编译器

一个用C++编写的Markdown编译器，可以将Markdown文本转换为兼容WebKit的HTML。

[English Documentation](README.md)

## 特性

- 支持无限级的标题（# ## ### 等）
- 支持复杂数学公式
  - 行内公式：使用单个 `$` 包裹
  - 边缘自动换行的行间公式：使用 `$$` 包裹
  - 等号自动换行的行间公式：使用 `$$$` 包裹
- 支持表格
- 支持化学式（使用Ketcher渲染）
  - 行内化学式：使用 `¥` 包裹
  - 行间化学式：使用 `¥¥` 包裹

## 系统要求

- C++17兼容的编译器
- CMake 3.10+（使用CMake构建时需要）
- 兼容Darwin和Linux平台

## 构建方法

### 使用CMake构建

```bash
mkdir -p build
cd build
cmake ..
make
```

### 使用构建脚本

```bash
chmod +x build.sh
./build.sh
```

## 使用方法

```bash
./bin/markdown_compiler 输入文件.md 输出文件.html
```

### 示例

```bash
./bin/markdown_compiler example.md example.html
```

## Markdown语法

### 标题

```
# 一级标题
## 二级标题
### 三级标题
```

### 数学公式

行内公式：
```
$E = mc^2$
```

行间公式：
```
$$
\sum_{i=1}^{n} i = \frac{n(n+1)}{2}
$$
```

等号对齐公式：
```
$$$
\begin{aligned}
a &= b + c \\
d &= e * f \\
g &= h - i
\end{aligned}
$$$
```

### 表格

```
| 表头1 | 表头2 | 表头3 |
| ----- | ----- | ----- |
| 单元格1 | 单元格2 | 单元格3 |
| 单元格4 | 单元格5 | 单元格6 |
```

### 化学式

行内化学式：
```
¥H2O¥
```

行间化学式：
```
¥¥
CH3COOH <=> CH3COO- + H+
¥¥
```

复杂分子结构：
```
¥¥
c1ccccc1
¥¥
```

## 注意事项

- 生成的HTML使用MathJax渲染数学公式
- 化学式使用Ketcher渲染
- HTML针对WebKit内核的浏览器进行了优化

## 许可证

MIT 