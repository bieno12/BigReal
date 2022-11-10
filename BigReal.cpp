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



	temp = matches[3].str();
	while(temp.size() != 0 && temp.back() == '0')
		temp.pop_back();
	if(temp.size() != 0)
	{
		this->fractionPart = BigDecimalInt(temp);
	}
	else
	{
		this->fractionPart = BigDecimalInt("0");
	}

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
    string num1 = fractionPart.getNumber(), num2 = other.fractionPart.getNumber();
    char sign1 = fractionPart.getsign(), sign2 = other.fractionPart.getsign();
    BigReal result;
    while (num1.size() < num2.size()) {
        num1 += '0';
    }
    while (num2.size() < num1.size()) {
        num2 += '0';
    }
    fractionPart.setNumber(num1);
    other.fractionPart.setNumber(num2);
    fractionPart.set_sign(sign1);
    other.fractionPart.set_sign(sign2);
    BigDecimalInt sumwhole = wholePart + other.wholePart;
    BigDecimalInt sumfrac = fractionPart + other.fractionPart;

    BigReal x = *this;
    if (m_sign == '-' && other.m_sign == '+') {
        x.fractionPart.set_sign('+');
        x.wholePart.set_sign('+');
        if ((x.fractionPart < other.fractionPart && x.wholePart > other.wholePart) || (x.fractionPart > other.fractionPart && x.wholePart < other.wholePart)) {
            int count = 1;
            for (int i = 0; i < fractionPart.size(); ++i) count *= 10;
            BigDecimalInt v(to_string(count)), vv("1");
            sumfrac.set_sign('+');
            sumfrac = v - sumfrac;
            if (sumwhole.sign() == 1) sumwhole = sumwhole - vv;
            else if (sumwhole.sign() == 0) sumwhole = sumwhole + vv;
        }
    }
    else if (m_sign == '+' && other.m_sign == '-') {
        x = other;
        x.fractionPart.set_sign('+');
        x.wholePart.set_sign('+');


        if ((x.fractionPart < fractionPart && x.wholePart > wholePart) || (x.fractionPart > fractionPart && x.wholePart < wholePart)) {
            int count = 1;
            for (int i = 0; i < fractionPart.size(); ++i) count *= 10;
            BigDecimalInt v(to_string(count)), vv("1");
            sumfrac.set_sign('+');
            sumfrac = v - sumfrac;
            if (sumwhole.sign() == 1) sumwhole = sumwhole - vv;
            else if (sumwhole.sign() == 0) sumwhole = sumwhole + vv;
        }
    }

    else if (m_sign == other.m_sign) {
        if (sumfrac.size() != fractionPart.size())
        {
            BigDecimalInt zz("1");
            string xx = result.fractionPart.getNumber();
            xx.erase(0, 1);
            sumfrac.setNumber(xx);
            sumwhole = sumwhole + zz;
        }

    }
    result.fractionPart = sumfrac;
    result.wholePart = sumwhole;
    result.wholePart.set_sign(sumwhole.getsign());
    result.m_sign = result.wholePart.getsign();

    return result;
}

BigReal BigReal::operator- (BigReal& other)
{
    
    BigReal x, result, c =*this;
    
    if(other.m_sign == '-')
    {   
        x = other;
        x.fractionPart.set_sign('+');
        x.wholePart.set_sign('+');
        result = x + c;
    }

    else
    {
        if(other.m_sign == '+')
        {
            x = other;
            x.fractionPart.set_sign('-');
            x.wholePart.set_sign('-');
            result = x + c;
        }
    }

    return result;
}
//third group (Abdul-rahman's Part)
bool BigReal::operator< (BigReal anotherReal)
{
    string num = wholePart.getNumber();
    string num2 = anotherReal.wholePart.getNumber();

    if (num[0] != num2[0] && num[0] == '-') return true; //false
    else if (num[0] != num2[0] && num2[0] == '-') return false; //true
   
    else {
        if (wholePart < anotherReal.wholePart) return true; //false
        else if (wholePart > anotherReal.wholePart) return false; //true
        
        else {
            if (fractionPart < anotherReal.fractionPart) return true; //true
            else return false;
        }
    }
    
}
bool BigReal::operator> (BigReal anotherReal)
{    
    string num = wholePart.getNumber();
    string num2 = anotherReal.wholePart.getNumber();

    if (num[0] != num2[0] && num[0] == '-') return false; //false
    else if (num[0] != num2[0] && num2[0] == '-') return true; //true

    else {
        if (wholePart < anotherReal.wholePart) return false; //false
        else if (wholePart > anotherReal.wholePart) return true; //true

        else {
            if (fractionPart > anotherReal.fractionPart) return true; //true
            else return false;
        }
    }
}
bool BigReal::operator== (BigReal anotherReal)
{
    string s2, s1 = wholePart.getNumber();
    s1 += fractionPart.getNumber();

    s2 = anotherReal.wholePart.getNumber();
    s2 += anotherReal.fractionPart.getNumber();

    if (m_sign != anotherReal.m_sign) return false;
    else {
        if (s1 == s2) return true;
        else return false;
    }
}
int BigReal::size()
{
    cout << "this length without the sign and (.)" << endl;
    string s1 = wholePart.getNumber();
    s1 += fractionPart.getNumber();
    return s1.size();
}
int BigReal::sign()
{
    if (m_sign == '+') return 1;
    else return 0;
}
ostream& operator << (ostream& out, const BigReal& num)
{
    BigReal x = num;
    
    out << x.str();
    return out;
}
istream& operator >> (istream& in, BigReal& num)
{
    string num_str;
    in >> num_str;
    num = BigReal(num_str);
    return in;
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