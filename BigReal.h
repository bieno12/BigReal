#include<iostream>
#include <string>
#include "BigDecimalIntClass.h"
using namespace std;

class BigReal {
private:
	int sign;
	int size;
	BigDecimalInt wholePart; // the left of the decimal point
	BigDecimalInt fractionPart; // the right of the decimal point
public:
	//first group
	BigReal (double realNumber = 0.0); // Default constructor
	BigReal (string realNumber);
	BigReal (BigDecimalInt bigInteger);
	BigReal (const BigReal& other); // Copy constructor
	BigReal (BigReal&& other); // Move constructor
	BigReal& operator= (BigReal& other); // Assignment operator
	BigReal& operator= (BigReal&& other); // Move assignment 

	//second group
	BigReal operator+ (BigReal& other);
	BigReal operator- (BigReal& other);
	//third group
	bool operator< (BigReal anotherReal); 
	bool operator> (BigReal anotherReal); 
	bool operator== (BigReal anotherReal); 
	int size(); 
	int sign();
	friend ostream& operator << (ostream& out, BigReal num);
	friend istream& operator >> (istream& out, BigReal num);
};
