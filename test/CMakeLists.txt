add_executable(TESTS 
    test_classroom.cpp
    test_graph.cpp
    test_node.cpp
    test_fileReaders.cpp
    test_path.cpp
)

target_include_directories(TESTS PRIVATE ../include)
target_link_libraries(TESTS PRIVATE graph file_handler program_manager GTest::gtest_main gmock)

include(GoogleTest)
gtest_discover_tests(TESTS)