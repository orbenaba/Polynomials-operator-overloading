#pragma once
#include<iostream>
using namespace std;
class Monomial
{
public:
	//empty+full~~~constructor
	Monomial(double coef = 0, int deg = 0, Monomial*next = NULL, Monomial*prev = NULL);
	//copy constructor
	Monomial(const Monomial&);
	//setters
	void setCoef(double);
	void setDeg(int);
	void setNext(Monomial*next);
	void setPrev(Monomial*prev);
	//getters
	double getCoef()const;
	int getDeg()const;
	Monomial*getNext()const;
	Monomial*getPrev()const;
	static int getNumberOfMonomials();
	void stringToMonomial(const string &str);

	//check if it possible to add another mono to original mono without turn over to poly
	~Monomial();
	//////////////////////////////////////////
	///////////OPERATOR OVERLOADING///////////
	//////////////////////////////////////////
	const Monomial&operator=(Monomial const&);
	//mono is 5X^4---->> 5X^4=1----->>mono now is 1X^4
	void operator=(double coef);

	const Monomial operator+(Monomial const&);
	const Monomial operator-(Monomial const&);
	const Monomial operator*(Monomial const&);
	void operator+=(Monomial const&);
	void operator-=(Monomial const&);
	void operator*=(Monomial const&);
	void operator-();//Unary
	bool operator==(Monomial const&)const;
	bool operator!=(Monomial const&)const;
	friend ostream&operator<<(ostream&, const Monomial&);
	friend istream&operator>>(istream&, Monomial&);
	double operator()(double)const;

	friend bool operator==(Monomial&, double);//global member
	friend bool operator==(double,Monomial&);//global member
	friend bool operator!=(Monomial&, double);//global member
	friend bool operator!=(double, Monomial&);//global member
	friend void operator*=(Monomial&,double);//global member


private:
	double coef;
	unsigned int deg;
	Monomial*next;
	Monomial*prev;
	static int numberOfMonomials;
};
