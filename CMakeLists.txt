cmake_minimum_required(VERSION 3.11)
project(RegExp2)

set(CMAKE_CXX_STANDARD_REQUIRED 11)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

add_executable("RegularExpressionsA" "RegularExpressionsA.c"   "RegularExpressionsA.h" "RegularExpressionsA_test.c"  )
add_executable("RegularExpressionsB" "RegularExpressionsB.cpp" "RegularExpressionsB.h" "RegularExpressionsB_test.cpp")
add_executable("RegularExpressionsC" "RegularExpressionsC.cpp" "RegularExpressionsC.h" "RegularExpressionsC_test.cpp")

file(GLOB SOURCES "*.cpp" "*.c" "*.h")
#exclude all _test files
list(FILTER SOURCES EXCLUDE REGEX ".*_test.*")
# show all files
add_executable("RegularExpressionsTest" ${SOURCES} "RegularExpressions_cross_test.cpp")
