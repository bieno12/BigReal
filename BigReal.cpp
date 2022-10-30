#include "BigReal.h"

using namespace std;



//first group (Zeyad's Part)


BigReal::BigReal(double realNumber = 0.0)
{

}
BigReal::BigReal(string realNumber)
{

}
BigReal::BigReal(BigDecimalInt bigInteger)
{

}
BigReal::BigReal(const BigReal& other)
{

}
BigReal::BigReal(BigReal&& other)
{

}

BigReal& BigReal::operator= (BigReal& other)
{

}

BigReal& BigReal::operator= (BigReal&& other)
{

}

//second group (Mohamed's Part)

BigReal& BigReal::operator+ (BigReal& other)
{

}
BigReal& BigReal::operator- (BigReal& other)
{

}
//third group (Abdul-rahman's Part)
bool BigReal::operator< (BigReal anotherReal)
{

}
bool BigReal::operator> (BigReal anotherReal)
{

}
bool BigReal::operator== (BigReal anotherReal)
{

}
int BigReal::size()
{

}
int BigReal::sign()
{

}
friend ostream& BigReal::operator << (ostream& out, BigReal num)
{

}
friend istream& BigReal::operator >> (istream& out, BigReal num)
{

}