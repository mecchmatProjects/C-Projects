// File EnvVar_test.c
// Realization of EnvVar
// Done by Tanya Voitsehivska (comp math 1)
// Date 06.12.2022
// Tests for EnvVAr


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <fenv.h>
#include <locale.h>
#include <stdbool.h>
#include "EnvVar_C.h"


// The function in which all functions of the module are called and their operation is checked.
// Enter data manually from the console (option 1) or from a test text file (option 2)
int main(int argc, char* argv[]) {
	// We create a variable that is responsible for the fact that all tests were successful
	bool check = true;


	char option1[20] = "";
	printf("Choose your option 1 or 2\n1 -> console input\n2 -> data from file\n=>");
	fgets(option1, 50, stdin);
	option1[strlen(option1) - 1] = '\0';

	printf("Option => %s\n",option1);

	// 1.0
	printf("Test 1.0:\n");
	if (task1_v0() == 0) {
		printf("Test 1.0 successfully passed\n");
	}
	else
	{
		printf("Test 1.0 failed\n");
		check = false;
	}

	// 1.1
	printf("Test 1.1:\n");
	if (task1_v1() == 0) {
		printf("Test 1.0 successfully passed\n");
	}
	else
	{
		printf("Test 1.0 failed\n");
		check = false;
	}



	// 2
	printf("Test 2:\n");
	if (task2() == 0) {
		printf("Test 2 successfully passed\n");
	}
	else
	{
		printf("Test 2 failed\n");
		check = false;
	}


	// 3
	printf("Test 3:\n");
	if (task3() == 0) {
		printf("Test 3 successfully passed\n");
	}
	else
	{
		printf("Test 3 failed\n");
		check = false;
	}


	// 4
	printf("Test 4:\n");
	if (task4(option1) == 0) {
		printf("Test 4 successfully passed\n");
	}
	else
	{
		printf("Test 4 failed\n");
		check = false;
	}

	// 5
	printf("Test 5:\n");
	if (task5(option1) == 0) {
		printf("Test 5 successfully passed\n");
	}
	else
	{
		printf("Test 5 failed\n");
		check = false;
	}

	// If all the tests were successful, then we create a file that means that all the tests were successful
	// (we will need this for the cross-test)
	if (check)
	{
		FILE* file;
		file = fopen("envvar_C_test_result.txt","w");
    	fclose(file);
	}

	return 0;
}
