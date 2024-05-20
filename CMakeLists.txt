cmake_minimum_required(VERSION 3.28)
project(RoutesOnWEITI)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(graph ./src/node.cpp ./src/graph.cpp ./src/classroom.cpp)
target_include_directories(graph PRIVATE ./include)

add_executable(graph_tests ./test/test_node.cpp ./test/test_graph.cpp ./test/test_classroom.cpp)

include(FetchContent)

FetchContent_Declare(
    SDL2
    URL  https://github.com/libsdl-org/SDL/releases/download/release-2.30.3/SDL2-2.30.3.tar.gz
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

add_library(program_manager ./src/program_manager.cpp)
target_include_directories(program_manager PRIVATE ./include)
target_link_libraries(program_manager PUBLIC SDL2main SDL2-static)

FetchContent_Declare(
    nlohmann_json
    URL https://github.com/nlohmann/json/archive/refs/tags/v3.11.3.tar.gz
)
FetchContent_MakeAvailable(nlohmann_json)

add_library(file_handle ./src/file_handle.cpp)
target_include_directories(file_handle PRIVATE ./include)
target_link_libraries(file_handle PUBLIC nlohmann_json graph)

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE program_manager file_handle graph)
target_include_directories(main PRIVATE ./include)