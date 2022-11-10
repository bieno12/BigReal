#include <iostream>
#include "BigReal.h"
using namespace std;

int main()
{
	BigReal num("+100");
	BigReal num1(0.0);
	char sign;
	while(true)
	{

		cin >> num  >> sign >> num1;
		if(sign == '+')
			cout  << num << " " << sign << " " << num1 << " = " << num + num1 << endl;
		else
			cout << num << " " << sign << " " << num1 << " = " << num - num1 << endl;

	}

}