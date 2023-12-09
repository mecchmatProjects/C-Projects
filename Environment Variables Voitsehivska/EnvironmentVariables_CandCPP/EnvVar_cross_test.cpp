// File EnvVar_cross_test.cpp
// Realization of EnvVar
// Done by Tanya Voitsehivska (comp math 1)
// Date 10.12.2022
// Cross tests for EnvVAr


#include <iostream>
#include <fstream>


int main()
{
    //Make sure you have run the following codes before running this code:
    // EnvVar_test_C.c ; EnvVar_test_CPP.cpp

    // Check if the files exist in the current directory
    // if they exist -> all tests in both languages were successful
    std::ifstream stream1("envvar_CPP_test_result.txt");
    std::ifstream stream2("envvar_C_test_result.txt");

    if (stream1.good() && stream2.good())
    {
        std::cout << "Success!" << std::endl;
    }
    else std::cout << "Failure :(" << std::endl;

    return 0;
}
