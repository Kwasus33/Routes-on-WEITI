cmake_minimum_required(VERSION 3.28)

project(RoutesOnWEITI)

set(CMAKE_CONFIGURATION_TYPES "Release;RelWithDebInfo" CACHE STRING "" FORCE)

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

FetchContent_Declare(
    nlohmann_json
    URL https://github.com/nlohmann/json/archive/refs/tags/v3.11.3.tar.gz
)
FetchContent_MakeAvailable(nlohmann_json)

add_library(file_handler ./src/file_handler.cpp)
target_include_directories(file_handler PRIVATE ./include)
target_link_libraries(file_handler PUBLIC nlohmann_json graph)

add_library( program_manager 
    ./src/program_manager.cpp 
    ./src/commands.cpp 
    ./src/input_manager.cpp 
    ./src/resource_manager.cpp 
    ./src/renderer.cpp
    ./src/logic_manager.cpp
    ./src/path.cpp
    )
target_include_directories(program_manager PRIVATE ./include)
target_link_libraries(program_manager PUBLIC file_handler graph SDL2main SDL2-static)

find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)
qt_standard_project_setup()

qt_add_library(GuiLogic
    ./src/mainwindow.cpp
    ./include/mainwindow.h
    ./forms/mainwindow.ui
)

target_link_libraries(GuiLogic PRIVATE program_manager file_handler graph Qt6::Core)
target_include_directories(GuiLogic PUBLIC ./include)

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE GuiLogic program_manager file_handler graph)
target_include_directories(main PRIVATE ./include)

