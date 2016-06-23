cmake_minimum_required(VERSION 3.2)
project(shell)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")
set(SOURCE_FILES src/main.cpp src/Shell.cpp src/Proc.cpp src/Parser.cpp)
set(INCLUDE_DIR include)

include_directories(${INCLUDE_DIR})
add_executable(shell ${SOURCE_FILES})
