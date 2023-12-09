// File EnvVar_test.cpp
// Realization of EnvVar
// Done by Tanya Voitsehivska (comp math 1)
// Date 10.12.2022
// Tests for EnvVAr

#include <iostream>
#include <algorithm>
#include <fenv.h>
#include <cstdio>
#include <string>
#include <locale>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <cstring>
#include <filesystem>
#include "EnvVar_CPP.h"


// The function in which all functions of the module are called and their operation is checked.
// Enter data manually from the console (option 1) or from a test text file (option 2)
int main() {
	// We create a variable that is responsible for the fact that all tests were successful
	bool check = true;

	std::string option1;
	printf("Choose your option 1 or 2\n1 -> console input\n2 -> data from file\n=>");
	std::getline(std::cin, option1);
	std::cout << "Your option => " << option1 << std::endl;


	// 1.0
	std::cout << "test 1.0:\n";
	if (task1_v0() == 0)
    {
        std::cout << "test 1 v0 successfully passed\n";
    }
	else
    {
        std::cout << "test 1 v0 failed\n";
		check = false;
    }

    // 1.1
	std::cout << "test 1.1:\n";
	if (task1_v1() == 0)
    {
        std::cout << "test 1 v1 successfully passed\n";
    }
	else
    {
        std::cout << "test 1 v1 failed\n";
		check = false;
    }

	//2
	std::cout << "Test 2:\n";
	if (task2() == 0) std::cout << "\nTest 2 successfully passed\n";
	else
	{
		std::cout << "Test 2 failed\n";
		check = false;
	}

	//3
	std::cout << "Test 3:\n";
	if (task3() == 0) std::cout << "Test 3 successfully passed\n";
	else
	{
		std::cout << "Test 3 failed\n";
		check = false;
	}

	//4
	std::cout << "Test 4:\n";
	if (task4(option1) == 0) std::cout << "Test 4 successfully passed\n";
	else
	{
		check = false;
		std::cout << "Test 4 failed\n";
	}

	//5
	std::cout << "Test 5:\n";
	if (task5(option1) == 0) std::cout << "Test 5 successfully passed\n";
	else
	{
		std::cout << "Test 5 failed\n";
		check = false;
	}

	// If all the tests were successful, then we create a file that means that all the tests were successful
	// (we will need this for the cross-test)
	if (check)
	{
		// Open a file for writing
  		std::ofstream file("envvar_CPP_test_result.txt");

  		// Check if the file was opened successfully
  		if (!file.is_open())
		{
    		std::cerr << "Failed to open file for writing!" << std::endl;
  		}

  		// Write some text to the file
  		file << "envvar_CPP_test_result" << std::endl;

  		// Close the file
  		file.close();
	}

	return 0;
}
