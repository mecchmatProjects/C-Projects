output: Histogram.o Histogram_Khomenko_test.o
	g++ Histogram.o Histogram_Khomenko_test.o -o Histogram_Khomenko_test

Histogram.o: ../src/Histogram.cpp
	g++ -c ../src/Histogram.cpp

Histogram_Khomenko_test.o: Histogram_Khomenko_test.cpp
	g++ -c Histogram_Khomenko_test.cpp

clean: 
	del *.o Histogram_Khomenko_test.exe Histogram_Khomenko_cross_test.exe

clean1: 
	rm *.o Histogram_Khomenko_test.exe Histogram_Khomenko_cross_test.exe