output: Histogram.o input_funcs.o Histogram_Khomenko_test.o
	gcc Histogram.o input_funcs.o Histogram_Khomenko_test.o -o Histogram_Khomenko_test

Histogram.o: ../src/Histogram.c
	gcc -c ../src/Histogram.c

input_funcs.o: ../src/input_funcs.c
	gcc -c ../src/input_funcs.c

Histogram_Khomenko_test.o: Histogram_Khomenko_test.c
	gcc -c Histogram_Khomenko_test.c

clean: 
	del *.o Histogram_Khomenko_test.exe

clean1: 
	rm *.o Histogram_Khomenko_test.exe