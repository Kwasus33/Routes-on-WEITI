cmake_minimum_required(VERSION 3.28)
project(RoutesOnWEITI)

add_library(graph ./src/node.cpp ./src/graph.cpp)
target_include_directories(graph PRIVATE ./include)

add_executable(graph_tests ./test/test_node.cpp ./test/test_graph.cpp)

include(FetchContent)

FetchContent_Declare(
    SDL2
    GIT_REPOSITORY  https://github.com/libsdl-org/SDL
    GIT_TAG         release-2.0.20
    GIT_PROGRESS    TRUE
)

FetchContent_Declare(
    SDL2_IMAGE
    GIT_REPOSITORY  https://github.com/libsdl-org/SDL_image
    GIT_TAG         97405e74e952f51b16c315ed5715b6b9de5a8a50
    GIT_PROGRESS    TRUE
)

FetchContent_MakeAvailable(SDL2 SDL2_IMAGE)

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

add_library(program_manager STATIC ./src/program_manager.cpp)
target_include_directories(program_manager PRIVATE ./include)
target_link_libraries(program_manager PUBLIC SDL2main SDL2-static SDL2_image)

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE program_manager)
target_include_directories(main PRIVATE ./include)