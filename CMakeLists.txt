cmake_minimum_required(VERSION 3.13)
project(Quaternion_Korzhuk C)

set(CMAKE_C_STANDARD 99)

add_executable(Quaternion_Korzhuk tests/Quaternion_test.c src/Point3D.c headers/Point3D.h src/Figure3D.c headers/Figure3D.h
        headers/Quaternion.h src/Quaternion.c headers/common.h tests/Quaternion_test.c src/Angle3D.c headers/Angle3D.h src/Edge3D.c headers/Edge3D.h src/Progections3D.c headers/Progections3D.h)