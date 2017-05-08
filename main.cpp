////////////////////////////////////////////////////////////////
// ELEX 4618 Template project for BCIT
// Name: Julie Lee
// ID: A00967975
// Date:
// Title:
////////////////////////////////////////////////////////////////
#include "Detect.h"

CDetect start;

int main()
{
	menu();

	while (1);
	return 0;
}

void menu() 
{
	char method;

	cout << "Please Choose the method of driving: \n"
		<< "Auto   (A) \n"
		<< "Manual (M) \n"
		<< endl;

	cin >> method;

	switch (method)
	{
	case 'A':
	case 'a':
		start.run();
		break;

	case 'M':
	case 'm':
		cout << "FWD (w) \n"
			<< "LEFT (a) \n"
			<< "RIGHT (d) \n"
			<< "REVERSE (s) \n"
			<< "Break (q) \n"
			<< "Servo (e) \n"
			<< "Stop (z)"
			<< endl;

		start.control();
		break;
	}
}

