cmake_minimum_required(VERSION 3.14)
project(Geometry3d C)

include_directories(src headers tests)

set(CMAKE_C_STANDARD 99)

add_executable(Geometry3d
        src/main.c src/line.c src/plane.c src/point.c src/segment.c src/vector.c src/triangle.c
        tests/line_test.c tests/point_test.c tests/triangle_test.c tests/vector_test.c src/pyramid.c tests/pyramid_test.c tests/pyramid_test.h src/common.c)

target_link_libraries(Geometry3d m)