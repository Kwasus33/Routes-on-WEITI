add_executable(TESTS 
    test_classroom.cpp
    test_graph.cpp
    test_node.cpp
    test_file_handler.cpp
)

target_include_directories(TESTS PRIVATE ../include)
target_link_libraries(TESTS PRIVATE graph GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(TESTS)