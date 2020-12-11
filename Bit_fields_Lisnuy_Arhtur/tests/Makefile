output: source test
	g++ Bit_fields.o Bit_fields_test.o -o Bit_fields_test_exe

source: ../src/Bit_fields.cpp
	g++ -c ../src/Bit_fields.cpp

test: Bit_fields_test.cpp
	g++ -c Bit_fields_test.cpp

clean: 
	rm *.o *.exe