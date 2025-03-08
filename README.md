# Markdown C++ Compiler

A C++ compiler for Markdown that converts Markdown text to HTML compatible with WebKit.

[中文文档](README_CN.md)

## Features

- Unlimited levels of headings (# ## ### etc.)
- Complex mathematical formulas
  - Inline formulas: enclosed in single `$`
  - Block formulas with automatic line breaks: enclosed in `$$`
  - Block formulas with automatic equation alignment: enclosed in `$$$`
- Tables
- Chemical formulas (using Ketcher)
  - Inline chemical formulas: enclosed in `¥`
  - Block chemical formulas: enclosed in `¥¥`

## Requirements

- C++17 compatible compiler
- CMake 3.10+ (for building with CMake)
- Compatible with Darwin and Linux platforms

## Building

### Using CMake

```bash
mkdir -p build
cd build
cmake ..
make
```

### Using build script

```bash
chmod +x build.sh
./build.sh
```

## Usage

```bash
./bin/markdown_compiler input.md output.html
```

### Example

```bash
./bin/markdown_compiler example.md example.html
```

## Markdown Syntax

### Headings

```
# Heading 1
## Heading 2
### Heading 3
```

### Mathematical Formulas

Inline formula:
```
$E = mc^2$
```

Block formula:
```
$$
\sum_{i=1}^{n} i = \frac{n(n+1)}{2}
$$
```

Aligned equations:
```
$$$
\begin{aligned}
a &= b + c \\
d &= e * f \\
g &= h - i
\end{aligned}
$$$
```

### Tables

```
| Header 1 | Header 2 | Header 3 |
| -------- | -------- | -------- |
| Cell 1   | Cell 2   | Cell 3   |
| Cell 4   | Cell 5   | Cell 6   |
```

### Chemical Formulas

Inline chemical formula:
```
¥H2O¥
```

Block chemical formula:
```
¥¥
CH3COOH <=> CH3COO- + H+
¥¥
```

Complex molecular structure:
```
¥¥
c1ccccc1
¥¥
```

## Notes

- The generated HTML uses MathJax for rendering mathematical formulas
- Chemical formulas are rendered using Ketcher
- The HTML is optimized for WebKit-based browsers

## License

MIT 