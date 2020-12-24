/* File  test_Date.c*/

#include "../src/Date.h"


/*check functions inputs and outputs*/
void test1_input_output() {
	FILE* file1;
	fopen_s(&file1, "Time1", "r");
	FILE* file2;
	fopen_s(&file2, "Time2", "r");
	if (file1 == NULL)
	{
		printf("Not such file");
		exit(1);
	}
	if (file2 == NULL)
	{
		printf("Not such file");
		exit(1);
	}
	TIME* Test1;
	Test1 = (TIME*)malloc(sizeof(TIME));
	TIME* Test2;
	Test2 = (TIME*)malloc(sizeof(TIME));

	inputTextFile_Date(file1, Test1);
	inputTextFile_Date(file2, Test2);
	FILE* file3;
	fopen_s(&file3, "test1_input_output", "w");
	outputTextFile_Date(file3, Test1);
	free(Test1);
	free(Test2);

	fclose(file1);
	fclose(file2);
	fclose(file3);
}
/*check functions next/previous*/
void test2_next_preious() {
	FILE* file1;
	fopen_s(&file1, "Time1", "r");
	if (file1 == NULL)
	{
		printf("Not such file");
		exit(1);
	}

	TIME* Test1;
	Test1 = (TIME*)malloc(sizeof(TIME));
	inputTextFile_Date(file1, Test1);

	FILE* file3;
	fopen_s(&file3, "test2_next_preious", "w");

	TIME* Result1;
	Result1 = (TIME*)malloc(sizeof(TIME));
	Result1 = next(Test1);
	fprintf(file3, "Next Date for first Date: ");
	outputTextFile_Date(file3, Result1);
	free(Result1);
	TIME* Result2;
	Result2 = (TIME*)malloc(sizeof(TIME));
	Result2 = previous(Test1);
	fprintf(file3, "\nPrevious Date for first Date: ");
	outputTextFile_Date(file3, Result2);
	free(Result2);
	free(Test1);

	fclose(file1);
	fclose(file3);
}

	/*check comparing function*/
void test3_compare_weekday() {
	FILE* file1;
	fopen_s(&file1, "Time1", "r");
	FILE* file2;
	fopen_s(&file2, "Time2", "r");
	if (file1 == NULL)
	{
		printf("Not such file");
		exit(1);
	}
	if (file2 == NULL)
	{
		printf("Not such file");
		exit(1);
	}

	TIME* Test1;
	Test1 = (TIME*)malloc(sizeof(TIME));
	inputTextFile_Date(file1, Test1);
	TIME* Test2;
	Test2 = (TIME*)malloc(sizeof(TIME));
	inputTextFile_Date(file2, Test2);

	FILE* file3;
	fopen_s(&file3, "test3_compare_weekday", "w");

	TIME* Result3;
	Result3 = (TIME*)malloc(sizeof(TIME));
	Result3 = which_is_earlier(Test1, Test2);
	fprintf(file3, "\nThis Date is earlier: ");
	outputTextFile_Date(file3, Result3);
	free(Result3);

	char* Result_char;
	Result_char = week_day(Test1);
	fprintf(file3, "\nThe weekday of first Date: %c", Result_char);

	free(Test1);
	free(Test2);

	fclose(file1);
	fclose(file2);
	fclose(file3);
}
	/*check functions which give days and math functions*/
void test4_days_math(){
	IType days = 17; //number of days which we will use latter
	FILE* file1;
	fopen_s(&file1, "Time1", "r");
	FILE* file2;
	fopen_s(&file2, "Time2", "r");
	if (file1 == NULL)
	{
		printf("Not such file");
		exit(1);
	}
	if (file2 == NULL)
	{
		printf("Not such file");
		exit(1);
	}

	TIME* Test1;
	Test1 = (TIME*)malloc(sizeof(TIME));
	inputTextFile_Date(file1, Test1);
	TIME* Test2;
	Test2 = (TIME*)malloc(sizeof(TIME));
	inputTextFile_Date(file2, Test2);

	FILE* file3;
	fopen_s(&file3, "test4_weekday_math", "w");

	NType res;
	res = days_from_beginning(Test1);
	fprintf(file3, "\nDays from first Date: %u", res);
	res = days_between(Test1, Test2);
	fprintf(file3, "\nDays between Dates: %u", res);

	
	TIME* Result4;
	Result4 = (TIME*)malloc(sizeof(TIME));
	Result4 = add_Date(Test1, Test2);
	fprintf(file3, "\nAdd Dates: ");
	outputTextFile_Date(file3, Result4);
	free(Result4);
	TIME* Result5;
	Result5 = (TIME*)malloc(sizeof(TIME));
	Result5 = sub_Date(Test1, Test2);
	fprintf(file3, "\nSubtract Dates: ");
	outputTextFile_Date(file3, Result5);
	free(Result5);
	TIME* Result6;
	Result6 = (TIME*)malloc(sizeof(TIME));
	Result6 = add_days(Test1, days);
	fprintf(file3, "\nAdd your days to first Date: ");
	outputTextFile_Date(file3, Result6);
	free(Result6);
	TIME* Result7;
	Result7 = (TIME*)malloc(sizeof(TIME));
	Result7 = subtract_days(Test1, days);
	fprintf(file3, "\nSubtract your days to first Date: ");
	outputTextFile_Date(file3, Result7);
	free(Result7);

	free(Test1);
	free(Test2);
	fclose(file1);
	fclose(file2);
	fclose(file3);
}