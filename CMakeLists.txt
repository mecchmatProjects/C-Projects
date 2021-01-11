cmake_minimum_required(VERSION 3.14)
project(cpp_project_tensor C CXX)

set(CMAKE_CXX_STANDARD 11)

add_executable(cpp_project_tensor main.cpp)
add_library(tensor STATIC src/tensor.hxx)
set_target_properties(tensor PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cpp_project_tensor tensor)

add_executable(test ./src/test.cpp)
