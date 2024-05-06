cmake_minimum_required(VERSION 3.28)
project(RoutesOnWEITI)

add_library(graph ./src/node.cpp)
target_include_directories(graph PRIVATE ./include)

add_executable(graph_tests ./test/test_node.cpp)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/master.zip
)
target_include_directories(graph_tests PRIVATE ./include)
target_link_libraries(graph_tests PRIVATE graph)

FetchContent_MakeAvailable(googletest)
enable_testing()

include(GoogleTest)

target_link_libraries(graph_tests PRIVATE GTest::gtest_main)
gtest_discover_tests(graph_tests)