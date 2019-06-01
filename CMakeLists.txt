cmake_minimum_required(VERSION 3.14)
project(spline_horbunov_kovaltchuk C)

set(CMAKE_C_STANDARD 99)

add_executable(spline_tests_horbunov_kovaltchuk tests/spline_tests_horbunov_kovaltchuk.c headers/spline_horbunov_kovaltchuk.h src/spline_horbunov_kovaltchuk.c)
