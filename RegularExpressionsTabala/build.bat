@echo off

rem Set directory variables
set BUILD_DIR=build
set EXE_DIR=%BUILD_DIR%\bin

rem Set compiler variables
set CC=gcc
set CXX=g++

rem Remove files from previous build
if exist %BUILD_DIR% rd /s /q %BUILD_DIR%
if exist %EXE_DIR% rd /s /q %EXE_DIR%

rem Create build directories if they don't exist
if not exist %BUILD_DIR% md %BUILD_DIR%
if not exist %EXE_DIR% md %EXE_DIR%

rem Compile RegularExpressionsA
echo Compiling RegularExpressionsA
%CC% -c RegularExpressionsA.c -o %BUILD_DIR%/RegularExpressionsA.o
%CC% -c RegularExpressionsA_test.c -o %BUILD_DIR%/RegularExpressionsA_test.o
%CC% %BUILD_DIR%/RegularExpressionsA.o %BUILD_DIR%/RegularExpressionsA_test.o -o %EXE_DIR%/RegularExpressionsA.exe

rem Compile RegularExpressionsB
echo Compiling RegularExpressionsB
%CXX% -c RegularExpressionsB.cpp -o %BUILD_DIR%/RegularExpressionsB.o
%CXX% -c RegularExpressionsB_test.cpp -o %BUILD_DIR%/RegularExpressionsB_test.o 
%CXX% %BUILD_DIR%/RegularExpressionsB.o %BUILD_DIR%/RegularExpressionsB_test.o -o %EXE_DIR%/RegularExpressionsB.exe

rem Compile RegularExpressionsC
echo Compiling RegularExpressionsC
%CXX% -c RegularExpressionsC.cpp -o %BUILD_DIR%/RegularExpressionsC.o
%CXX% -c RegularExpressionsC_test.cpp -o %BUILD_DIR%/RegularExpressionsC_test.o
%CXX% %BUILD_DIR%/RegularExpressionsC.o %BUILD_DIR%/RegularExpressionsC_test.o -o %EXE_DIR%/RegularExpressionsC.exe

rem Compile RegularExpressionsTest
echo Compiling RegularExpressionsTest
%CXX% %BUILD_DIR%/RegularExpressionsA.o %BUILD_DIR%/RegularExpressionsB.o %BUILD_DIR%/RegularExpressionsC.o RegularExpressions_cross_test.cpp -o %EXE_DIR%/RegularExpressionsTest.exe
