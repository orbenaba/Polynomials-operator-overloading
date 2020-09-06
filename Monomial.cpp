#pragma once
#include<math.h>
#include<string>
#include "Monomial.h"
using namespace std;
int Monomial::numberOfMonomials = 0;
//full+empty~~~~~~constructor
Monomial::Monomial(double coef, int deg, Monomial*next, Monomial*prev)
{
	setCoef(coef);
	setDeg(deg);
	setNext(next);
	setPrev(prev);
	numberOfMonomials++;//counter++
}
//copy constructor
Monomial::Monomial(const Monomial&other)
{
	setCoef(other.getCoef());
	setDeg(other.getDeg());
	setNext(other.getNext());
	setPrev(other.getPrev());
	numberOfMonomials++;//counter++
}
//destuctor
Monomial::~Monomial()
{
	numberOfMonomials--;//counter--
}
////////////
////setters
///////////
void Monomial::setCoef(double coef) { this->coef = coef; }
void Monomial::setDeg(int deg) { this->deg = deg; }
void Monomial::setNext(Monomial*next) { this->next = next; }
void Monomial::setPrev(Monomial*prev) { this->prev = prev; }
////////////
////getters
///////////
double Monomial::getCoef()const { return this->coef; }
int Monomial::getDeg()const { return this->deg; }
Monomial*Monomial::getNext()const { return this->next; }
Monomial*Monomial::getPrev()const { return this->prev; }
int Monomial::getNumberOfMonomials() { return numberOfMonomials; }
//////////////////////////////////////////
///////////OPERATOR OVERLOADING///////////
//////////////////////////////////////////
//operator ==(((global member)))
bool operator==(Monomial&m,double coef)
{
	return m.getCoef() == coef && m.getDeg() == 0||m.getCoef()==0&&coef==0;
}


//operator ==(((global member)))
bool operator==(double coef,Monomial&m)
{
	return m == coef;
}


//operator !=(((global member)))
bool operator!=(Monomial&m, double coef)
{
	return !(m == coef);
}


//operator !=(((global member)))
bool operator!=(double coef, Monomial&m)
{
	return !(coef == m);
}


//operator *=(((global member)))
void operator*=(Monomial&m, double d)
{
	m.setCoef(m.getCoef()*d);
}


//operator =
const Monomial&Monomial::operator=(Monomial const&other)
{
	setDeg(other.getDeg());
	setCoef(other.getCoef());
	setNext(other.getNext());
	setPrev(other.getNext());
	return *this;//in order to concatenate next monos
}

//mono is 5X^4---->> 5X^4=1----->>mono now is 1X^4
void Monomial::operator=(double coef)
{
	setCoef(coef);
}


//operator+
const Monomial Monomial::operator+(Monomial const&other)
{
	Monomial sum;
	if (this->deg != other.getDeg())
	{
		sum.setCoef(this->coef);
		sum.setDeg(this->deg);
	}
	else if (other.getCoef() + this->coef)
	{
		sum.setCoef(other.getCoef() + this->coef);
		sum.setDeg(other.getDeg());
	}
	return sum;
}


//operator -
const Monomial Monomial::operator-(Monomial const&other)
{
	Monomial sub;
	if (this->deg != other.getDeg())
	{
		sub.setCoef(this->coef);
		sub.setDeg(this->deg);
	}
	if (other.getCoef() - this->coef)
	{
		sub.setCoef(this->coef-other.getCoef());
		sub.setDeg(other.getDeg());
	}
	return sub;
}


//operator *
const Monomial Monomial::operator*(Monomial const&other)
{
	Monomial product;//default: coef=0,deg=0
	if (this->coef &&other.getCoef())//if both other and this arent ZERO
	{
		product.setCoef(this->coef*other.getCoef());
		product.setDeg(this->deg + other.getDeg());
	}
	return product;
}


//operator +=
void Monomial::operator+=(Monomial const&add)
{
	if (this->deg == add.getDeg())
		setCoef(getCoef() + add.getCoef());
}


//operator -=
void Monomial::operator-=(Monomial const&sub)
{
	if (this->deg == sub.getDeg())
		setCoef(getCoef() - sub.getCoef());
}


//operator *=
void Monomial::operator*=(Monomial const&pro)
{
	setDeg(pro.getDeg() + getDeg());
	setCoef(pro.getCoef() * getCoef());
}


//operator -(unary)
void Monomial::operator-()
{
	setCoef(getCoef()*(-1));
}


//operator ==(((class member)))
bool Monomial::operator==(Monomial const&other)const
{
	return (getDeg() == other.getDeg() && getCoef() == other.getCoef())||(getDeg()==0&&other.getDeg()==0);
}


//operator != (((class member)))
bool Monomial::operator!=(Monomial const&other)const
{
	return !(*this == other);
}


//operator <<(output)
ostream&operator<<(ostream&buf, const Monomial&m)
{
	if (m.getCoef()==0)
	{
		buf << 0;
		return buf;
	}
	//if (m.getCoef() == -1)
	//{
	//	if (m.getDeg() == 0)
	//		buf << -1;
	//	else if (m.getDeg() == 1)
	//		buf << "-x";
	//	else
	//		buf << "-x^" << m.getDeg();
	//}
	else if (m.getCoef() == 1)
	{
		if (m.getDeg() == 0)
			buf << 1;
		else if (m.getDeg() == 1)
			buf << 'x';
		else
			buf << "x^" << m.getDeg();
	}
	else
	{
		if (m.getDeg() == 0)
			buf << m.getCoef();
		else if (m.getDeg() == 1)
			buf << m.getCoef() << "*x";
		else
			buf << m.getCoef() << "*x^" << m.getDeg();
	}
	return buf;
}


//operator >>(input)
istream&operator>>(istream&buf, Monomial&m)
{
	string str;
	getline(buf, str);
	m.stringToMonomial(str);
	return buf;
}


//operator ()
//example: 3X^3(1)->->->->3 returned
double Monomial::operator()(double num)const
{
	return getCoef()*pow(num, getDeg());
}


void Monomial::stringToMonomial(const string &str)
{
	string temp = "";
	int i, size = str.length();
	bool flag = false;
	this->deg = 0; //reset the deg
	for (i = 0; i < size && str[i] != 'x'&&str[i]!='X'; i++)
		temp += str[i];
	if (temp != "")
		this->coef = stod(temp);
	else
		this->coef = 1;
	for (temp = ""; i < size; i++) {
		if (str[i] == 'x'||str[i]=='X')
			this->deg = 1;
		else if
			(str[i] == '^') flag = true;
		else if 
			(flag) temp += str[i];
	}
	if (flag)
		this->deg = stoi(temp);
}
