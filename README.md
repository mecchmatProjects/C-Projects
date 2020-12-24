# (C/СPP)-Projects
'Histogram_Khomenko_C/tests/Makefile': ввести в командному рядку(консолі) відкритому(ій) в папці 'Histogram_Khomenko_C/tests/' команду 'mingw32-make' або просто 'make' зележить від компілятора для створення виконуваного файла 'Histogram_Khomenko_test.exe' - тести проекта на С.

'Histogram_Khomenko_CPP/tests/Makefile' ввести в командному рядку(консолі) відкритому(ій) в папці 'Histogram_Khomenko_CPP/tests/' команду 'mingw32-make' або просто 'make' зележить від компілятора для створення виконуваного файла 'Histogram_Khomenko_test.exe' - тести проекта на СPP.

'Histogram_Khomenko_CPP/tests/Makefile1' ввести в командному рядку(консолі) відкритому(ій) в папці 'Histogram_Khomenko_CPP/tests/' команду 'mingw32-make -f Makefile1' або просто 'make -f Makefile1' зележить від компілятора для створення виконуваного файла 'Histogram_Khomenko_cross_test.exe' - кросс_тести проектів на С і СPP.

*Histogram_Khomenko_cross_test.exe - не зможе запуститись без попередніх запусків Histogram_Khomenko_test.exe з папок 'Histogram_Khomenko_C/tests' та 'Histogram_Khomenko_CPP/tests', які створять по файлу Histogram_compare_cross_test.txt (файл з данними тестування проекта на С чи СPP) відповідно у кожній директорії ('Histogram_Khomenko_CPP/tests' та 'Histogram_Khomenko_C/tests').

# Interpolation project
to compile both cpp and c projects at once use this command in terminal:

gcc Interpolation_Tyshchenko_C/tests/interpolation_tyshchenko_test.c Interpolation_Tyshchenko_C/src/interpolation_tyshchenko.c -o cproject && g++ Interpolation_Tyshchenko_CPP/tests/interpolation_tyshchenko_test.cpp Interpolation_Tyshchenko_CPP/src/interpolation_tyshchenko.cpp -o cppproject

then run cproject and cppproject

//you have to be in Interpolation_Tyshchenko folder in terminal//

to compile cross test file:

g++ cross_test_interpolation -o cross


