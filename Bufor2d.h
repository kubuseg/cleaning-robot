#pragma once
#include <list>
#include "Punkt2d.h"
class Bufor2d
{
private:
	std::list<Punkt2d> bufor;
	std::list<Punkt2d>::iterator iter;
public:
	Bufor2d();
	void addToList(Punkt2d);
	void addToList(double, double);
	Punkt2d getNext();
};