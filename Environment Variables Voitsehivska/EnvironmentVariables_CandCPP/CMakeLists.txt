cmake_minimum_required(VERSION 3.11)
project(RegExp2)

set(CMAKE_CXX_STANDARD_REQUIRED 11)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

add_executable("RegularExpressionsA" "EnvVar_C.c"   "EnvVar_C.h" "EnvVar_C_test.c"  )
add_executable("RegularExpressionsB" "EnvVar_CPP.cpp" "EnvVar_CPP.h" "EnvVar_CPP_test.cpp")

file(GLOB SOURCES "*.cpp" "*.c" "*.h")
#exclude all _test files
list(FILTER SOURCES EXCLUDE REGEX ".*_test.*")
# show all files
add_executable("RegularExpressionsTest" ${SOURCES} "RegularExpressions_cross_test.cpp")
