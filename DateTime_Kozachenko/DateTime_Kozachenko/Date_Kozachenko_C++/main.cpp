/* File  main.cpp*/

#include "src/Time.h"
#include "src/Date.h"

int main() {
	try {
		int definder = 0;
		std::cout << "Hi! Choose please, what you want to do: \n1)from console with Date\n2)from console with Time\n";
		std::cin >> definder;
		if (definder == 1) {
			Date D1;
			Date D2;
			Date Help;
			int number; 
			int help;
			std::cout << "Enter first Date: ";
			std::cin >> D1;
			std::cout << "Enter second Date, you may need it: ";
			std::cin >> D2;
			std::cout << "Enter number, which we may use to add or etc: ";
			std::cin >> number;
			
			std::cout << "First Date is: " << D1 << std::endl;
			std::cout << "Second Date is: " << D2 << std::endl;
			Help = D1.next();
			std::cout << "Next day of first Date is: " << Help << std::endl;
			Help = D2.next();
			std::cout << "Next day of second Date is: " << Help << std::endl;
			std::cout << "\nNow we will compare both of this Dates:\n";
			std::cout << D1 << " == " << D2 << "?\n";
			if (D1 == D2) {
				std::cout << "true\n";
			}
			else {
				std::cout << "false\n";
			}
			std::cout << D1 << " != " << D2 << "?\n";
			if (D1 != D2) {
				std::cout << "true\n";
			}
			else {
				std::cout << "false\n";
			}
			std::cout << D1 << " < " << D2 << "?\n";
			if (D1 < D2) {
				std::cout << "true\n";
			}
			else {
				std::cout << "false\n";
			}
			std::cout << D1 << " <= " << D2 << "?\n";
			if (D1 <= D2) {
				std::cout << "true\n";
			}
			else {
				std::cout << "false\n";
			}
			std::cout << D1 << " > " << D2 << "?\n";
			if (D1 > D2) {
				std::cout << "true\n";
			}
			else {
				std::cout << "false\n";
			}
			std::cout << D1 << " >= " << D2 << "?\n";
			if (D1 >= D2) {
				std::cout << "true\n";
			}
			else {
				std::cout << "false\n";

			}
			std::cout << "\nNow we will do some math with both of this Dates and number:\n";
			// Check addition of two dates
			std::cout << D1 << " + " << D2 << " = ";
			Help = D1 + D2;
			std::cout << Help << "\n";
			// Check subtraction of two dates
			std::cout << D1 << " - " << D2 << " = ";
			Help = D1 - D2;
			std::cout << Help << "\n";
			// Check addition of date and number
			std::cout << D1 << " + " << number << " = ";
			Help = D1.add_days(number);
			std::cout << Help << "\n";
			// Check subtraction of date and number
			std::cout << D1 << " - " << number << " = ";
			Help = D1.subtract_days(number);
			std::cout << Help << "\n";
			//Check days from the beggining
			std::cout << D1 << " from the beginning: ";
			help = D1.days_from_beginning();
			std::cout << help << "\n";
			//Check days between
			std::cout << "Days between: " << D1 << " and " << D2;
			help = days_between(D1, D2);
			std::cout << help << "\n";
			std::cout << "\nFor this date: " << D1 << "\nWeekday is: " << D1.week_day() << "\n";
		}
		else if (definder == 2) {
			Time T1;
			Time T2;
			Date D1;
			Time Help;
			int number;
			int help;
			std::cout << "Enter first Time: ";
			std::cin >> T1;
			std::cout << "Enter second Time, you may need it: ";
			std::cin >> T2;
			std::cout << "Enter a Date, you may need it: ";
			std::cin >> D1;
			std::cout << "Enter number, which we may use to add or etc: ";
			std::cin >> number;
			std::cout << "First Time is: " << T1 << std::endl;
			std::cout << "Second Time is: " << T2 << std::endl;
			std::cout << "\nNow we will compare both of this Times:\n";
			std::cout << T1 << " == " << T2 << " : ";
			help = T1 == T2;
			std::cout << help << "\n";
			std::cout << T1 << " != " << T2 << " : ";
			help = T1 != T2;
			std::cout << help << "\n";
			std::cout << T1 << " > " << T2 << " : ";
			help = T1 > T2;
			std::cout << help << "\n";
			std::cout << T1 << " >= " << T2 << " : ";
			help = T1 >= T2;
			std::cout << help << "\n";
			std::cout << T1 << " < " << T2 << " : ";
			help = T1 < T2;
			std::cout << help << "\n";
			std::cout << T1 << " <= " << T2 << " : ";
			help = T1 <= T2;
			std::cout << help << "\n";
			std::cout << "\nNow we will do some math with both of this Times and number:\n";
			std::cout << T1 << " + " << T2 << " : ";
			Help = T1 + T2;
			std::cout << Help << "\n";
			std::cout << T1 << " - " << T2 << " : ";
			Help = T1 - T2;
			std::cout << Help << "\n";
			std::cout << T1 << " * " << number << " : ";
			Help = T1 * number;
			std::cout << Help << "\n";
			std::cout << T1 << " / " << number << " : ";
			Help = T1 / number;
			std::cout << Help << "\n";
			std::cout << "\nNow we will do some math with both of this Times and Dates:\n";
			Help = convert_date(D1);
			std::cout << "From " << D1 << " to time you get:\n " << help;
			Date help1 = add_date(D1, T1);
			std::cout << "If we add " << D1 << " and " << T1 << " we get: " << help1 << "\n";
			help1 = subtract_date(D1, T1);
			std::cout << "If we subtract " << D1 << " and " << T1 << " we get: " << help1 << "\n";

		}
		else {
		std::string error = "Input from console wrong";
		throw error;
}
	}
	catch (std::string er) {
		std::cout << er << std::endl;
		return 1;
	}
}