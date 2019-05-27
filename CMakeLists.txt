cmake_minimum_required(VERSION 3.13)
project(Quaternion)
set(CMAKE_C_STANDARD 99)
add_executable(Quaternion headers/Quaternion.h headers/common.h src/Quaternion.c headers/Point3D.h src/Point3D.c headers/Figure3D.h src/Figure3D.c src/Edge3D.c headers/Edge3D.h src/Angle3D.c headers/Angle3D.h src/Progections3D.c headers/Progections3D.h tests/Quaternion_test.c)