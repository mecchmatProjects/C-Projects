# (C/СPP)-Projects
'Histogram_Khomenko_C/tests/Makefile' ввести в командному рядку 'mingw32-make' або просто 'make' зележить від компілятора для створення виконуваного файла 'Histogram_Khomenko_test.exe' - тести проекта на С.

'Histogram_Khomenko_CPP/tests/Makefile' ввести в командному рядку 'mingw32-make' або просто 'make' зележить від компілятора для створення виконуваного файла 'Histogram_Khomenko_test.exe' - тести проекта на СPP.

'Histogram_Khomenko_CPP/tests/Makefile1' ввести в командному рядку 'mingw32-make -f Makefile1' або просто 'make -f Makefile1' зележить від компілятора для створення виконуваного файла 'Histogram_Khomenko_cross_test.exe' - кросс_тести проектів на С і СPP.

*Histogram_Khomenko_cross_test.exe - не зможе запуститись без попередніх запусків Histogram_Khomenko_test.exe з папок 'Histogram_Khomenko_C/tests' та 'Histogram_Khomenko_CPP/tests', які створять по файлу Histogram_compare_cross_test.txt (файл з данними тестування проекта на С чи СPP) відповідно у кожній директорії ('Histogram_Khomenko_CPP/tests' та 'Histogram_Khomenko_C/tests').
