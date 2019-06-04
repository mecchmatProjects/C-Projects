cmake_minimum_required(VERSION 3.14)
project(geometry2d_nobok_kormushka C)

set(CMAKE_C_STANDARD 99)

add_executable(geometry2d_nobok_kormushka src/geometry2d_nobok_kormushka.c headers/common.h headers/geometry2d_nobok_kormushka.h tests/geometry2d_nobok_kormushka.c)

target_link_libraries(geometry2d_nobok_kormushka m)
