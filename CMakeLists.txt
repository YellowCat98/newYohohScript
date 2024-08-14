cmake_minimum_required(VERSION 3.10)
project(YohohoScript)

file(GLOB SOURCES
    src/*.cpp
    src/*.hpp
    src/frontend/*.cpp
    src/frontend/*.hpp
    src/runtime/*.hpp
    src/runtime/*.cpp
)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add executable
add_executable(yhs ${SOURCES})
