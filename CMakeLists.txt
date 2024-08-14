cmake_minimum_required(VERSION 3.10)
project(yhs)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the fmt subdirectory


file(GLOB SOURCES
    src/*.cpp
    src/*.hpp
    src/frontend/*.cpp
    src/frontend/*.hpp
    src/runtime/*.hpp
    src/runtime/*.cpp
)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})

include(FetchContent)

FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt
  GIT_TAG        e69e5f977d458f2650bb346dadf2ad30c5320281) # 10.2.1
FetchContent_MakeAvailable(fmt)

target_link_libraries(${PROJECT_NAME} fmt::fmt)