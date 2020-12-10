/* File  Date.h*/

#include "../common.h"

extern TIME* generate_Date(IType year, IType month, IType day, IType hour, IType min, IType sec); // "constructor"
//extern void edit_Date(TIME D); //Supporting for adding/subtracting days, which edit date

extern void input_Date(TIME* D); // //function for input from console
extern void output_Date(TIME* D); //function for output to console
extern void inputTextFile_Date(FILE* file, TIME* D); // function for input from file
extern void outputTextFile_Date(FILE* File, TIME* D);//function for output to file

extern TIME* next(TIME* D); // Next day of the date
extern TIME* previous(TIME* D); // Previous day of the date

extern TIME* which_is_earlier(TIME* D1, TIME* D2); //comparing function 
extern char* week_day(TIME* D); // Name of weekday

extern NType days_from_beginning(TIME* D); // Amount of days from 01.01.0000 to the given date
extern NType days_between(TIME* D1, TIME* D2);//Days between two given dates

/*math functions*/
extern TIME* add_Date(TIME* D1, TIME* D2); //Add Dates
extern TIME* sub_Date(TIME* D1, TIME* D2); //Subtract Dates
extern TIME* add_days(TIME* D, IType days); // Add number of days
extern TIME* subtract_days(TIME* D, IType days); // Subtract number of days

