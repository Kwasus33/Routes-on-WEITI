cmake_minimum_required(VERSION 3.28)
project(RoutesOnWEITI)

add_library(graph ./src/node.cpp ./src/graph.cpp)
target_include_directories(graph PRIVATE ./include)

add_executable(graph_tests ./test/test_node.cpp ./test/test_graph.cpp)

include(FetchContent)

FetchContent_Declare(
    SDL2
    URL https://www.libsdl.org/release/SDL2-2.0.14.tar.gz
    GIT_TAG 97405e74e952f51b16c315ed5715b6b9de5a8a50
)
FetchContent_MakeAvailable(SDL2)

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

add_library(renderer ./src/renderer.cpp)
target_include_directories(renderer PRIVATE ./include)
target_link_libraries(renderer PUBLIC SDL2main SDL2-static)

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE renderer)
target_include_directories(main PRIVATE ./include)