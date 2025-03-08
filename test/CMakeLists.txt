file(GLOB_RECURSE TEST_SOURCES "*.cpp")

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