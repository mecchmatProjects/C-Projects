/* File C_RegularExpressions_test.h
Realization of header for test func
Done by Smakula Vladuslav (group: computer methematics 1)
Date 05.12.2023
*/
#ifndef C_REGULAREXPRESSIONS_TEST_H
#define C_REGULAREXPRESSIONS_TEST_H
#ifdef __cplusplus
extern "C" {
#endif

/**
* Performs regular expression tests for C funcs.
*
* @param bypass_check Flag to bypass user input for test mode selection (1 for automatic).
* @return 0 on successful execution.
*
* If bypass_check is set to 1, the function automatically runs automated tests; otherwise,
* it prompts the user to choose between manual and automatic test modes.
*/
int RegularExpressionsTestC(int bypass_check);

#ifdef __cplusplus
}
#endif

#endif // C_REGULAREXPRESSIONS_TEST_H