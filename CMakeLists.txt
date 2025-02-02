cmake_minimum_required(VERSION 3.28)
project(RoutesOnWEITI)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(graph ./src/node.cpp ./src/graph.cpp ./src/classroom.cpp)

add_library( program_manager 
    ./src/program_manager.cpp 
    ./src/commands.cpp 
    ./src/input_manager.cpp 
    ./src/resource_manager.cpp 
    ./src/renderer.cpp
    ./src/logic_manager.cpp
    ./src/console_interface.cpp
    ./src/path.cpp
    ./src/floor.cpp
    )

add_library( file_handler 
    ./src/file_handler.cpp
    ./src/jsonReader.cpp
    ./src/csvReader.cpp
)

add_library( parser
    ./src/argParser.cpp
)

set_target_properties(graph program_manager file_handler parser PROPERTIES COMPILE_FLAGS "-Wall -Wpedantic")

target_include_directories(graph PRIVATE ./include)
target_include_directories(parser PRIVATE ./include)

option(BUILD_TESTS "Build tests" OFF)

include(FetchContent)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/master.zip
    )
    FetchContent_MakeAvailable(googletest)
endif()

FetchContent_Declare(
    SDL2
    URL  https://github.com/libsdl-org/SDL/releases/download/release-2.30.3/SDL2-2.30.3.tar.gz
)
FetchContent_MakeAvailable(SDL2)

FetchContent_Declare(
    nlohmann_json
    URL https://github.com/nlohmann/json/archive/refs/tags/v3.11.3.tar.gz
)
FetchContent_MakeAvailable(nlohmann_json)


target_include_directories(file_handler PRIVATE ./include)
target_link_libraries(file_handler PUBLIC nlohmann_json graph)

target_include_directories(program_manager PRIVATE ./include)
target_link_libraries(program_manager PUBLIC file_handler graph SDL2main SDL2-static)

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE parser program_manager file_handler graph)
target_include_directories(main PRIVATE ./include)
