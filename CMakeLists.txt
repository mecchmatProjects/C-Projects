cmake_minimum_required(VERSION 3.14)
project(rational_sulyma_horbunov C)

set(CMAKE_C_STANDARD 99)

add_executable(rational_sulyma_horbunov src/rational_sulyma_horbunov_trukhan.c headers/rational_sulyma_horbunov_trukhan.h headers/common.h tests/rational_tests_sulyma_horbunov_trukhan.c)
