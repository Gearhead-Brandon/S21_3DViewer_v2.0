cmake_minimum_required(VERSION 3.0)

project(BrickGame LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_COMPILER "/usr/bin/gcc")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++ -std=c++17 -Wall -Werror -Wextra") 

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets OpenGLWidgets)

file(GLOB MAIN
    "./main.cpp"
)

file(GLOB_RECURSE SOURCE_FILES
    "./app/*.h"
    "./app/*.cpp"
    "./app/*.c"
)

# Create an executable target
add_executable(3DViewer ${MAIN} ${SOURCE_FILES})

# Add necessary libraries or dependencies
target_link_libraries(
    3DViewer
    Qt6::Core 
    Qt6::Gui 
    Qt6::Widgets
    Qt6::OpenGLWidgets
    -lstdc++
    -lm
)