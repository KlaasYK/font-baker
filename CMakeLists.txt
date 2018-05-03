cmake_minimum_required(VERSION 3.2)
project(fontbaker)

find_package(Freetype REQUIRED)
include_directories(${FREETYPE_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++17 -O2")
add_executable(baker main.cpp lodepng.cpp lodepng.h)
target_link_libraries(baker ${FREETYPE_LIBRARIES})
