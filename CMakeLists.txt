cmake_minimum_required(VERSION 3.13)
project(GeomND_melekestseva_stoychik)

set(CMAKE_C_STANDARD 99)

include_directories(BEFORE src)
include_directories(BEFORE tests)

add_library(GeomND  MODULE src/GeomND.h src/GeomND.c)

add_executable(test_GeomND tests/test_GeomND.c)