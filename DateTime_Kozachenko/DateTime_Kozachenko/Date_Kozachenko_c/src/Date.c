/* File  Date.c */

#include "Date.h"

//Supporting array of max amount of days of month
int days_in_month[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
//Supporting array of names of month
//Supporting array of names of day
char* days_of_week[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };


// "constructor"
TIME* generate_Date(IType year, IType month, IType day, IType hour, IType min, IType sec) {
	TIME* Time;
	Time = (struct tm1*) malloc(sizeof(TIME));
	Time->tm_year = year - 1900;
	if (month < 12 && month >= 0) {
		Time->tm_mon = month - 1;
	}
	if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)) {
		if (day < 29 && day > 0) {
			Time->tm_mday = day;
		}
	}
	else if (month == 2) {
		if (day < 28 && day > 0) {
			Time->tm_mday = day;
		}
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11) {
		if (day < 30 && day > 0) {
			Time->tm_mday = day;
		}
	}
	else {
		if (day < 31 && day > 0) {
			Time->tm_mday = day;
		}
	}

	if (hour < 24 && hour >= 0) {
		Time->tm_hour = hour;
	}
	if (min < 60 && min >= 0) {
		Time->tm_min = min;
	}
	if (sec < 60 && sec >= 0) {
		Time->tm_sec = sec;
	}
	return Time;
}

void edit_Date(TIME* D)
{
	int month_days = days_in_month[D->tm_mon];
	if ((D->tm_year % 4 == 0 && D->tm_year % 100 != 0) || D->tm_year % 400 == 0) {
		month_days++;
	}
	IType index = D->tm_mon;
	while (D->tm_mday > month_days) {
		D->tm_mday -= month_days;
		D->tm_mon++;
		index++;
		if (D->tm_mon == 13) {
			D->tm_mon = 1;
			D->tm_year++;
			index = 1;
		}
		month_days = days_in_month[index - 1];
		if (D->tm_mon == 2 && ((D->tm_year % 4 == 0 && D->tm_year % 100 != 0) || D->tm_year % 400 == 0))
		{
			D->tm_mon++;
		}
	}
	while (D->tm_mday <= 0) {
		D->tm_mon--;
		index--;
		if (D->tm_mon == 0) {
			D->tm_year--;
			D->tm_mon = 12;
			index = 12;
		}
		month_days = days_in_month[index - 1];
		if (D->tm_mon == 2 && !(D->tm_year % 400 % 4)) {
			month_days++;
		}
		D->tm_mday += month_days;
	}
}

// //function for input from console
void input_Date(TIME* D) {
	printf("Write date please like yyyy/mm/dd hh:mm:ss");
	IType y;
	IType m;
	IType d;
	IType h;
	IType m;
	IType s;
	scanf_s("%04d/%02d/%02d %02d:%02d:%02d", &y, &m, &d, &h, &m, &s);
	D->tm_year = y - 1900;
	D->tm_mon = m - 1;
	D->tm_mday = d;
	D->tm_hour = h;
	D->tm_min = m;
	D->tm_sec = s;
}
//function for output to console
void output_Date(TIME* D) {
	printf("%04d/%02d/%02d %02d:%02d:%02d", D->tm_year - 1900, D->tm_mon - 1, D->tm_mday, D->tm_hour, D->tm_min, D->tm_sec);
}
// function for input from file
void inputTextFile_Date(FILE* file, TIME* D) {
	IType y;
	IType m;
	IType d;
	IType h;
	IType m;
	IType s;
	fscanf_s(file, "%04d/%02d/%02d %02d:%02d:%02d", &y, &m, &d, &h, &m, &s);
	D->tm_year = y - 1900;
	D->tm_mon = m - 1;
	D->tm_mday = d;
	D->tm_hour = h;
	D->tm_min = m;
	D->tm_sec = s;
}
//function for output to file
void outputTextFile_Date(FILE* file, TIME* D) {
	fprintf(file, "%04d/%02d/%02d %02d:%02d:%02d", D->tm_year - 1900, D->tm_mon - 1, D->tm_mday, D->tm_hour, D->tm_min, D->tm_sec);
}


// Next day of the date
TIME* next(TIME* D) {
	IType year = D->tm_year + 1900;
	IType month = D->tm_mon + 1900;
	IType day = D->tm_mday;
	if (((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) && month == 2) {
		if (day < 29) {
			return generate_Date(year, month, ++day, D->tm_hour, D->tm_min, D->tm_sec);
		}
		else {
			return generate_Date(year, ++month, 1, D->tm_hour, D->tm_min, D->tm_sec);
		}
	}
	else if (month == 2) {
		if (day < 28) {
			return generate_Date(year, month, ++day, D->tm_hour, D->tm_min, D->tm_sec);
		}
		else {
			return generate_Date(year, ++month, 1, D->tm_hour, D->tm_min, D->tm_sec);
		}
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11) {
		if (day < 30) {
			return generate_Date(year, month, ++day, D->tm_hour, D->tm_min, D->tm_sec);
		}
		else {
			return generate_Date(year, ++month, 1, D->tm_hour, D->tm_min, D->tm_sec);
		}
	}
	else if (month == 12) {
		if (day < 31) {
			return generate_Date(year, month, ++day, D->tm_hour, D->tm_min, D->tm_sec);
		}
		else {
			return generate_Date(++year, 1, 1, D->tm_hour, D->tm_min, D->tm_sec);
		}
	}
	else {
		if (day < 31) {
			return generate_Date(year, month, ++day, D->tm_hour, D->tm_min, D->tm_sec);
		}
		else {
			return generate_Date(year, ++month, 1, D->tm_hour, D->tm_min, D->tm_sec);
		}
	}
}
// Previous day of the date
TIME* previous(TIME* D) {
	IType year = D->tm_year + 1900;
	IType month = D->tm_mon + 1900;
	IType day = D->tm_mday;
	if (year % 4 == 0 && month == 3) {
		if (day == 1) {
			return generate_Date(year, --month, 29, D->tm_hour, D->tm_min, D->tm_sec);
		}
		else {
			return generate_Date(year, month, day--, D->tm_hour, D->tm_min, D->tm_sec);
		}
	}
	else if (month == 3 && year % 4 != 0) {
		if (day == 1) {
			return generate_Date(year, --month, 28, D->tm_hour, D->tm_min, D->tm_sec);
		}
		else {
			return generate_Date(year, month, --day, D->tm_hour, D->tm_min, D->tm_sec);
		}
	}
	else if (month == 5 || month == 6 || month == 10 || month == 12) {
		if (day == 1) {
			return generate_Date(year, --month, 30, D->tm_hour, D->tm_min, D->tm_sec);
		}
		else {
			return generate_Date(year, month, --day, D->tm_hour, D->tm_min, D->tm_sec);
		}
	}
	else if (month == 1) {
		if (day == 1) {
			return generate_Date(--year, 12, 31, D->tm_hour, D->tm_min, D->tm_sec);
		}
		else {
			return generate_Date(year, month, --day, D->tm_hour, D->tm_min, D->tm_sec);
		}
	}
	else {
		if (day == 1) {
			return generate_Date(year, --month, 31, D->tm_hour, D->tm_min, D->tm_sec);
		}
		else {
			return generate_Date(year, month, --day, D->tm_hour, D->tm_min, D->tm_sec);
		}
	}
}
/* comparing functions */
TIME* which_is_earlier(TIME* D1, TIME* D2)
{
	NType days_D1 = days_from_beginning(D1);
	NType days_D2 = days_from_beginning(D2);
	IType differ = days_D1 - days_D2;
	if (differ < 0) {
		return D1;
	}
	else{
		return D2;
	}
}
// Name of weekday
char* week_day(TIME* D)
{
	IType a = (14 - D->tm_mon) / 12;
	IType y = D->tm_year - a;
	IType m = D->tm_mon + 12 * a - 2;
	return days_of_week[(D->tm_mday + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12) % 7];
}
// Amount of days from 01.01.0000 to the given date
NType days_from_beginning(TIME* D)
{
	NType year_help = D->tm_year + 1900;
	NType month_help = D->tm_mon + 1;
	NType day_help = D->tm_mday;
	if (month_help < 3) {
		year_help--;
		month_help += 12;
	}
	return ((year_help + 1) * 365 + year_help / 4 - year_help / 100 + year_help / 400 + (153 * month_help - 457) / 5 + day_help - 306);
}
//Days between two given dates
NType days_between(TIME* D1, TIME* D2)
{
	NType res1 = days_from_beginning(D1);
	NType res2 = days_from_beginning(D2);
	return(abs(res1 - res2));
}
/*math functions*/
TIME* add_Date(TIME* D1, TIME* D2)
{
	NType difference = days_between(D1, D2);
	TIME* result;
	TIME* Help = which_is_earlier(D1, D2);
	if (Help->tm_mday >= D1->tm_mday && Help->tm_mon >= D1->tm_mon && Help->tm_year >= D1->tm_year) {
		result = add_days(D2, difference);
		return	result;
	}
	else {
		result = add_days(D1, difference);
		return	result;
	}
}
TIME* sub_Date(TIME* D1, TIME* D2)
{
	NType difference = days_between(D1, D2);
	TIME* result;
	TIME* Help = which_is_earlier(D1, D2);
	if (Help->tm_mday >= D1->tm_mday && Help->tm_mon >= D1->tm_mon && Help->tm_year >= D1->tm_year) {
		result = subtract_days(D1, difference);
		return	result;
	}
	else {
		result = subtract_days(D2, difference);
		return	result;
	}
}
// Add number of days
TIME* add_days(TIME* D, IType days)
{
	TIME* Result = generate_Date(D->tm_year, D->tm_mon, D->tm_mday, D->tm_hour, D->tm_min, D->tm_sec);
	Result->tm_mday += days;
	edit_Date(Result);
	return Result;
}
// Subtract number of days
TIME* subtract_days(TIME* D, IType days)
{
	TIME* Result = generate_Date(D->tm_year, D->tm_mon, D->tm_mday, D->tm_hour, D->tm_min, D->tm_sec);
	Result->tm_mday -= days;
	edit_Date(Result);
	return Result;
}
