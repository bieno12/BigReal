#include "BigReal.h"
#include <stdexcept>
#include <algorithm>
using namespace std;
#define all(x) x.begin(),x.end()
static const string fractionExp = R"(^\s*([+-])*(\d+)(?:\.(\d+))?\s*$)";

//first group (Zeyad's Part)

BigReal::BigReal(double realNumber) : BigReal(to_string(realNumber))
{

}
BigReal::BigReal(string realNumber)
{
	regex fraction_regex(fractionExp);
	smatch 	matches;
	if(!regex_match(realNumber, matches, fraction_regex)){
		throw invalid_argument("invalid floating point number");
	}

	string numstr = matches[2].str();
	this->wholePart.setNumber(numstr);
	string temp = matches[1];

	if(count(all(temp), '-') % 2 )
		this->m_sign = '-';
	else
		this->m_sign = '+';


	if(matches.size() > 3)
		this->fractionPart = BigDecimalInt(matches[3].str());
	else
		this->fractionPart = BigDecimalInt(0);

	this->m_size = wholePart.size() + fractionPart.size();

}
BigReal::BigReal(BigDecimalInt bigInteger)
{
	this->m_sign = bigInteger.sign();
	this->wholePart = bigInteger;
	this->fractionPart = BigDecimalInt(0);
	this->m_size = wholePart.size() + fractionPart.size();
}
BigReal::BigReal(const BigReal& other)
{
	this->m_sign = other.m_sign;
	this->m_size = other.m_size;
	this->wholePart = other.wholePart;
	this->fractionPart = other.fractionPart;
}
BigReal::BigReal(BigReal&& other) 
	: m_sign(move(other.m_sign)) 
	, m_size(move(other.m_size))
	, wholePart(move(other.wholePart))
	, fractionPart(move(other.fractionPart))
{
	//we don't need to nullify any pointers because std string already does that when moved
}

BigReal& BigReal::operator= (BigReal& other)
{
	this->m_sign = other.m_sign;
	this->m_size = other.m_size;
	this->wholePart = other.wholePart;
	this->fractionPart = other.fractionPart;
	return *this;
}

BigReal& BigReal::operator= (BigReal&& other)
{
	this->m_sign = move(other.m_sign);
	this->m_size = move(other.m_size);
	this->wholePart = move(other.wholePart);
	this->fractionPart = move(other.fractionPart);
	return *this;
}

//second group (Mohamed's Part)

BigReal BigReal::operator+ (BigReal& other)
{

	return other;
}
BigReal BigReal::operator- (BigReal& other)
{

	return other;
}
//third group (Abdul-rahman's Part)
bool BigReal::operator< (BigReal anotherReal)
{
	return 1;
}
bool BigReal::operator> (BigReal anotherReal)
{
	return 1;
}
bool BigReal::operator== (BigReal anotherReal)
{
	return 1;
}
int BigReal::size()
{
	return 1;
}
int BigReal::sign()
{
	return 1;
}
ostream& operator << (ostream& out, const BigReal& num)
{
	return out;
}
istream& operator >> (istream& out, const BigReal& num)
{
	return out;
}

//additional functions

string BigReal::str()
{
	string res;
	if(m_sign == '-')
		res += m_sign;
	res = res + wholePart.getNumber() + "." + fractionPart.getNumber();
	return res;
}