cmake_minimum_required(VERSION 3.10)
project(markdown_cpp VERSION 1.0)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 添加include目录
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# 添加源文件
file(GLOB CORE_SOURCES "src/core/*.cpp")
file(GLOB PARSER_SOURCES "src/parser/*.cpp")
file(GLOB RENDERER_SOURCES "src/renderer/*.cpp")
file(GLOB UTILS_SOURCES "src/utils/*.cpp")
file(GLOB APP_SOURCES "src/app/*.cpp")

# 创建库
add_library(markdown_core STATIC ${CORE_SOURCES})
add_library(markdown_parser STATIC ${PARSER_SOURCES})
add_library(markdown_renderer STATIC ${RENDERER_SOURCES})
add_library(markdown_utils STATIC ${UTILS_SOURCES})

# 设置库依赖关系
target_link_libraries(markdown_parser PRIVATE markdown_core markdown_utils)
target_link_libraries(markdown_renderer PRIVATE markdown_core markdown_utils)

# 创建可执行文件
add_executable(markdown_compiler ${APP_SOURCES})
target_link_libraries(markdown_compiler 
    markdown_core 
    markdown_parser 
    markdown_renderer 
    markdown_utils
)

# 安装目标
install(TARGETS markdown_compiler DESTINATION bin)
install(TARGETS markdown_core markdown_parser markdown_renderer markdown_utils
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib)

# 添加测试
enable_testing()

# 添加测试可执行文件
file(GLOB TEST_SOURCES "test/*.cpp")
foreach(test_source ${TEST_SOURCES})
    get_filename_component(test_name ${test_source} NAME_WE)
    add_executable(${test_name} ${test_source})
    target_link_libraries(${test_name} 
        markdown_core 
        markdown_parser 
        markdown_renderer 
        markdown_utils
    )
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach() 