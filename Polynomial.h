#pragma once
#include"Monomial.h"
using namespace std;
class Polynomial
{
public:
	//FULL&DEFAULT CONSTRUCTOR
	Polynomial(Monomial*tail = NULL, Monomial*head = NULL, int deg = 0);
	Polynomial(Polynomial const&);
	//DESTRUCTOR
	~Polynomial();
	//getters
	Monomial*getHead()const;
	Monomial*getTail()const;
	int getDeg()const;
	//setters
	void setHead(Monomial*);
	void setTail(Monomial*);
	void setDeg(int deg);
	//////////////////////////////////////////
	///////////OPERATOR OVERLOADING///////////
	//////////////////////////////////////////
	void clear();
	bool operator==(Monomial const&)const;
	bool operator!=(Monomial const&)const;

	const Polynomial operator=(Polynomial const&);

	const Polynomial operator+(Monomial const &);
	const Polynomial operator+(Polynomial const &);
	const Polynomial operator-(Monomial const&);
	const Polynomial operator-(Polynomial const&);

	void operator+=(Polynomial const&);
	void operator-=(Polynomial const&);
	void operator+=(Monomial const&);
	void operator-=(Monomial const&);

	void operator-();//Unary
	bool operator==(Polynomial const&)const;
	bool operator!=(Polynomial const&)const;
	friend ostream&operator<<(ostream&, Polynomial const&);
	friend istream&operator>>(istream&, Polynomial&);
	double operator()(double)const;
	double operator[](int const deg)const;//taking out
	void add(const Monomial& other);
private:
	Monomial * head;
	Monomial*tail;
	int deg;
};


