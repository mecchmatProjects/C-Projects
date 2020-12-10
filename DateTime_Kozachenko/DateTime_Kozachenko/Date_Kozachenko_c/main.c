/* File  main.c */

#include "/src/Date.h"

int main() {
	TIME* Test1;
	Test1= (TIME*) malloc(sizeof(TIME));
	TIME* Test2;
	Test2 = (TIME*) malloc(sizeof(TIME));
	IType days; //number of days which we will use latter
	printf("Write me number of days which you want, please: ");
	scanf_s("%d", &days);

	/*check functions inputs and outputs*/
	printf("Write down first Time: ");
	input_Date(Test1);
	printf("Write down second Time: ");
	input_Date(Test2);
	printf("First Date:");
	output_Date(Test1);
	printf("\nSecond Date: ");
	output_Date(Test2);

	/*check functions next/previous*/
	TIME* Result1;
	Result1 = (TIME*)malloc(sizeof(TIME));
	Result1 = next(Test1);
	printf("\nNext Date for first Date: ");
	output_Date(Result1);
	free(Result1);
	TIME* Result2;
	Result2 = (TIME*)malloc(sizeof(TIME));
	Result2 = previous(Test1);
	printf("\nPrevious Date for first Date: ");
	output_Date(Result2);
	free(Result2);

	/*check comparing function*/
	TIME* Result3;
	Result3 = (TIME*)malloc(sizeof(TIME));
	Result3 = which_is_earlier(Test1, Test2);
	printf("\nThis Date is earlier: ");
	output_Date(Result3);
	free(Result3);

	/*check weekday function*/
	char* Result_char;
	Result_char = week_day(Test1);
	printf("\nThe weekday of first Date: %c", Result_char);

	/*check functions which give days*/
	NType res;
	res = days_from_beginning(Test1);
	printf("\nDays from first Date: %u", res);
	res = days_between(Test1, Test2);
	printf("\nDays between Dates: %u", res);

	/*Check math functions*/
	TIME* Result4;
	Result4 = (TIME*)malloc(sizeof(TIME));
	Result4 = add_Date(Test1, Test2);
	printf("\nAdd Dates: ");
	output_Date(Result4);
	free(Result4);
	TIME* Result5;
	Result5 = (TIME*)malloc(sizeof(TIME));
	Result5 = sub_Date(Test1, Test2);
	printf("\nSubtract Dates: ");
	output_Date(Result5);
	free(Result5);
	TIME* Result6;
	Result6 = (TIME*)malloc(sizeof(TIME));
	Result6 = add_days(Test1, days);
	printf("\nAdd your days to first Date: ");
	output_Date(Result6);
	free(Result6);
	TIME* Result7;
	Result7 = (TIME*)malloc(sizeof(TIME));
	Result7 = subtract_days(Test1, days);
	printf("\nSubtract your days to first Date: ");
	output_Date(Result7);
	free(Result7);

	free(Test1);
	free(Test2);
}