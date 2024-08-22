cmake_minimum_required(VERSION 3.0)

project(BrickGame LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_COMPILER "/usr/bin/gcc")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -fprofile-arcs -ftest-coverage") 

file(GLOB SOURCE_FILES
    "./*.cpp"
)

file (GLOB AFFINE_TRANSFORMATIONS
    "../app/Model/Components/AffineTransformations/Move/*.cpp"
    "../app/Model/Components/AffineTransformations/Scale/*.cpp"
    "../app/Model/Components/AffineTransformations/Rotate/*.cpp"
    "../app/Model/Components/Figure/*.cpp"
    "../app/Model/Components/FileReader/*.cpp"
    "../app/Common/FacadeOpResult/*.cpp"
)

# Create a library target
add_library(AffineTransformations STATIC ${AFFINE_TRANSFORMATIONS})

# Create an executable target
add_executable(tests ${SOURCE_FILES})

# Add necessary libraries or dependencies
target_link_libraries(
    tests
    AffineTransformations
    -lstdc++ 
    -std=c++17
    -lgtest
    -lm
)

set_target_properties(
    tests
    PROPERTIES
    COMPILE_FLAGS "-fprofile-arcs -ftest-coverage"
    LINK_FLAGS "--coverage"
    ENABLE_TESTING TRUE
)