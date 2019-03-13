#include "pch.h"
#include <iostream>
#include <fstream>

using namespace std;

class lista;
class Nod
{
private:
	Nod *prev_nod;
	float valoare;
	Nod *next_nod;
public:
	Nod(float value);
	friend class lista;
	friend ostream& operator<<(ostream& input, lista& l);
};

class lista
{
	Nod* elementStart;
	Nod* elementFinal;
	lista createCopy();
public:
	lista()
	{
		elementStart = NULL;
		elementFinal = NULL;
	}
	void addEnd(float value);
	void addEnd(float values[]);
	void addFront(float value);
	void addFront(float values[]);
	bool isEmpty();
	void deleteFront();
	void deleteEnd();
	friend ostream& operator<<(ostream& input, lista& l);
	lista operator+(lista l);
};

Nod::Nod(float value)
{
	prev_nod = NULL;
	valoare = value;
	next_nod = NULL;
}

bool lista::isEmpty()
{
	return this->elementStart == NULL;
}

lista lista::createCopy()
{
	lista l;
	Nod *p = this->elementStart;
	while(p!=NULL)
	{
		l.addEnd(p->valoare);
		p = p->next_nod;
	}
	return l;
}

void lista::addEnd(float value)
{
	Nod* d = new Nod(value);
	if (isEmpty())
	{
		elementStart = d;
		elementFinal = d;
		return;
	}
	elementFinal->next_nod = d;
	d->prev_nod = elementFinal;
	elementFinal = d;
}

void lista::addEnd(float values[])
{
	const int length = sizeof(values) / sizeof(float);
	for (auto i = 0; i < length; i++)
		addEnd(values[i]);
}

void lista::addFront(float value)
{
	Nod* d = new Nod(value);
	if (isEmpty())
	{
		elementStart = d;
		elementFinal = d;
		return;
	}
	elementStart->prev_nod = d;
	d->next_nod = elementFinal;
	elementFinal = d;
}

void lista::addFront(float values[])
{
	const int length = sizeof(values) / sizeof(float);
	for (auto i = 0; i < length; i++)
		addFront(values[i]);
}

istream& operator>>(istream& input, lista& l)
{
	float val;
	while (input.good())
	{
		input >> val;
		l.addEnd(val);
	}
	return input;
}

ostream& operator<<(ostream& output, lista& l)
{
	Nod *p = l.elementStart;
	while (p!= NULL)
	{
		output << p->valoare << " ";
		p = p->next_nod;
	}
	cout << endl;
	p = l.elementFinal;
	while (p != NULL)
	{
		output << p->valoare << " ";
		p = p->prev_nod;
	}
	cout << endl;
	return output;
}

void lista::deleteEnd()
{
	if(elementFinal == elementStart)
	{
		elementFinal = NULL;
		elementStart = NULL;
		return;
	}
	Nod *p = elementFinal;
	elementFinal = elementFinal->prev_nod;
	elementFinal->next_nod = NULL;
	delete(p);
}

void lista::deleteFront()
{
	if (elementFinal == elementStart)
	{
		elementFinal = NULL;
		elementStart = NULL;
		return;
	}
	Nod *p = elementStart;
	elementStart = elementStart->next_nod;
	elementStart->prev_nod = NULL;
	delete(p);
}

lista lista::operator+(lista l)
{
	lista lista_n = this->createCopy();
	Nod *p = l.elementStart;
	while (p != NULL)
	{
		lista_n.addEnd(p->valoare);
		p = p->next_nod;
	}
	return lista_n;
}

int main()
{
	ifstream f1("date1.in");
	lista l1;
	f1 >> l1;
	l1.addEnd(34.5);
	l1.deleteFront();
	cout << l1;
	f1.close();
	cout << endl << endl;
	ifstream f2("date2.in");
	lista l2;
	f2 >> l2;
	cout << l2;
	f2.close();
	cout << endl << endl;

	lista l = l1 + l2;
	cout << l;
}
