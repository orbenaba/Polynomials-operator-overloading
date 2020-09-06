#pragma once
#include "Polynomial.h"
#include<string>
using namespace std;
//constructors
Polynomial::Polynomial(Monomial * tail, Monomial * head, int deg)
{
	this->tail = tail;
	this->head = head;
	this->deg = deg;
}
Polynomial::Polynomial(Polynomial const&other)
{
	if (!other.getHead())
		this->head = this->tail = NULL;
	else
	{
		Monomial*header = other.getHead()->getNext(), *runner, *temp;
		this->head = new Monomial(*other.getHead());
		this->head->setPrev(NULL);
		runner = this->head;
		while (header)
		{
			temp = new Monomial(*header);
			runner->setNext(temp);
			temp->setPrev(runner);
			runner = runner->getNext();
			header = header->getNext();
		}
		runner->setNext(NULL);
		this->tail = runner;
	}
}
//DESTRUCTOR
Polynomial::~Polynomial()
{
	clear();
}
//setters
void Polynomial::setHead(Monomial*head) { this->head = head; }
void Polynomial::setTail(Monomial*tail) { this->tail = tail; }
void Polynomial::setDeg(int deg) { this->deg = deg; }
//getters
Monomial*Polynomial::getHead()const { return this->head; }
Monomial*Polynomial::getTail()const { return this->tail; }
int Polynomial::getDeg()const { return this->deg; }
//////////////////////////////////////////
///////////OPERATOR OVERLOADING///////////
//////////////////////////////////////////
void Polynomial::clear()
{
	Monomial*runner;
	while (head)
	{
		runner = head;
		head = head->getNext();
		delete runner;
	}
	head = tail = NULL;
}

//(((poly==mono)))
bool Polynomial::operator==(Monomial const&m)const
{
	return getHead() && getHead() == getTail() && (m.getDeg() == getHead()->getDeg() && m.getCoef() == getHead()->getCoef() || m.getCoef() == 0 && getHead()->getCoef() == 0);
}


//(((poly!=mono)))
bool Polynomial::operator !=(Monomial const&m)const
{
	return !(*this == m);
}


//operator =
const Polynomial Polynomial::operator=(Polynomial const&other)
{
	Monomial*temp = head, *runner = other.getHead(), *inserted; 
	clear();
	head = tail = new Monomial(*other.getHead());
	if (runner)
		runner = runner->getNext();
	temp = head;
	while (runner)
	{
		inserted = new Monomial(*runner);
		temp->setNext(inserted);
		inserted->setPrev(temp);
		temp = temp->getNext();
		runner = runner->getNext();
	}
	temp->setNext(NULL);
	tail = temp;
	return *this;
}


//operator + (((Poly+Mono)))
const Polynomial Polynomial::operator+(Monomial const&other)
{
	Polynomial sum(*this);
	sum.add(other);
	return sum;
}


//operator -(((Poly+Mono))) (Binary)
const Polynomial Polynomial::operator-(Monomial const&other)
{
	Monomial m(other);
	Polynomial sum(*this);
	-m;
	sum.add(m);
	return sum;
}


//operator + (((Poly+Poly)))
const Polynomial Polynomial::operator+(Polynomial const&other)
{
	Monomial*runner = other.getHead();
	Polynomial sum;
	sum = *this + *runner;
	if (runner)
		runner = runner->getNext();
	while (runner)
	{
		sum = sum + (*runner);
		runner = runner->getNext();
	}
	return sum;
}


//operator - (((Poly-Poly)))
const Polynomial Polynomial::operator-(Polynomial const&other)
{
	Monomial*runner = other.getHead();
	Polynomial sub(*this);
	- (*runner);
	if (runner)
		runner = runner->getNext();
	while (runner)
	{
		sub = sub - (*runner);
		runner = runner->getNext();
	}
	return sub;
}


//operator -(Unary)
void Polynomial::operator-()
{
	Monomial*runner = this->head;
	while (runner)
	{
		-(*runner);
		runner = runner->getNext();
	}
}


//operator += (((Poly+=Mono)))
void Polynomial::operator+=(Monomial const&other)
{
	(*this) = (*this) + other;
}


//operator -= (((Poly-=Mono)))
void Polynomial::operator-=(Monomial const&other)
{
	(*this) = (*this) - other;
}


//operator += (((Poly+=Poly)))
void Polynomial::operator+=(Polynomial const&other)
{
	(*this) = (*this) + other;
}


//operator -= (((Poly-=Poly)))
void Polynomial::operator-=(Polynomial const&other)
{
	(*this) = (*this) - other;
}


//operator == (((Poly==Poly)))
bool Polynomial::operator==(Polynomial const&other)const
{
	Monomial*temp1 = this->head, *temp2 = other.getHead();
	while (temp1&&temp2)
	{
		if (*temp1 != *temp2)
			return false;
		temp1 = temp1->getNext();
		temp2 = temp2->getNext();
	}
	if (!temp1 && !temp2)
		return true;
	return false;
}


//operator == (((Poly==Poly)))
bool Polynomial::operator!=(Polynomial const&other)const
{
	return !((*this) == other);
}


//operator << output
ostream&operator<<(ostream&buf, Polynomial const &p)
{
	if (p.getHead() == NULL||p.getTail()==NULL)
	{
		buf << 0;
		return buf;
	}
	Monomial*runner = p.getHead();
	buf << *runner;
	runner = runner->getNext();
	while (runner)
	{
		if (runner->getCoef() > 0)
			buf << '+';
		buf << *runner;
		runner = runner->getNext();
	}
	return buf;
}


//operator >> input
istream&operator>>(istream&buf, Polynomial&p)
{
	p.clear();
	string str,substr;
	Monomial runner;
	getline(buf, str);
	int i, size = str.length();
	substr = str[0];
	if (size == 1)
	{
		runner.setCoef(atoi(&str[0]));
		runner.setDeg(0);
		p += runner;
	}
	for (i = 1; i < size; i++)
	{
		if (str[i] != '-'&&str[i] != ','&&str[i] != '+')
			substr += str[i];
		else
		{
			runner.stringToMonomial(substr);
			p += runner;
			runner.setCoef(0);
			runner.setDeg(0);
			substr = str[i];
		}
	}
	return buf;
}


//operator ()
double Polynomial::operator()(double num)const
{
	double sum = 0;
	Monomial*runner = this->head;
	while (runner)
	{
		sum += (*runner)(num);
		runner = runner->getNext();
	}
	return sum;
}


//operator [] (((taking out)))
//(return 5X^3+5X^2+1)[2]->->->->return 5

double Polynomial::operator[](int const deg)const
{
	Monomial*runner = this->head;
	if (runner->getDeg() < deg)
		return 0;
	while (runner&&runner->getDeg() > deg)
		runner = runner->getNext();
	if (runner&&runner->getDeg() == deg)
		return runner->getCoef();
	return 0;
}

//add single monomial to an existed polynomial
void Polynomial::add(const Monomial& other)
{
	Monomial copy(other);
	if (!tail && !head)
	{
		Monomial*inserted = new Monomial(other);
		head = tail = inserted;
		setDeg(other.getDeg());
		return;
	}
	if (other.getCoef() == 0)
		return;
	if (head->getDeg() < other.getDeg())
	{
		Monomial*inserted = new Monomial(other);
		inserted->setNext(head);
		head->setPrev(inserted);
		head = head->getPrev();
		setDeg(other.getDeg());
		return;
	}
	if (head->getDeg() == other.getDeg())
	{
		if (head->getCoef() + other.getCoef())
			head->setCoef(head->getCoef() + other.getCoef());
		else
		{
			Monomial*temp = head;
			if (head == tail)
			{
				head = tail = NULL;
				setDeg(0);
			}
			else
			{
				head = head->getNext();
				head->setPrev(NULL);
				setDeg(head->getDeg());
			}
			delete temp;
		}
		return;
	}
	Monomial*runner = head;
	while (runner->getNext() && runner->getDeg() > other.getDeg())
		runner = runner->getNext();
	if (!runner->getNext()&& runner->getDeg() > other.getDeg())
	{
		Monomial*inserted = new Monomial(copy);
		runner->setNext(inserted);
		inserted->setPrev(runner);
		tail = runner->getNext();
		return;
	}
	if (runner->getDeg() == other.getDeg())
	{
		if (runner->getCoef() + other.getCoef())
			runner->setCoef(runner->getCoef() + other.getCoef());
		else
		{
			Monomial*deleted = runner;
			runner = runner->getPrev();
			runner->setNext(deleted->getNext());
			delete deleted;
			deleted = runner->getNext();
			if (deleted)
				deleted->setPrev(runner);
		}
		return;
	}
	if (runner->getDeg() < other.getDeg())
	{
		Monomial*temp = runner->getPrev(),*inserted=new Monomial(copy);
		temp->setNext(inserted);
		inserted->setPrev(temp);
		inserted->setNext(runner);
		runner->setPrev(inserted);
	}
	if (runner->getDeg() > other.getDeg())
	{
		runner->setNext(&copy);
		copy.setPrev(runner);
	}
}
