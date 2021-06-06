#include "Bufor2d.h"

Bufor2d::Bufor2d() {
	bufor.push_back(Punkt2d(0, 0));
	iter = bufor.begin();
}

void Bufor2d::addToList(Punkt2d nowyPunkt)
{
	double odleglosc = nowyPunkt.magnitude();

	for (std::list<Punkt2d>::iterator iter = bufor.begin(); iter != bufor.end(); )
	{
		if ((*iter).magnitude() > odleglosc)
			iter++;
		else
		{
			bufor.insert(iter, nowyPunkt);
			break;
		}
	}
}

void Bufor2d::addToList(double horizontal, double vertical)
{
	Punkt2d nowyPunkt = Punkt2d(horizontal, vertical);
	double odleglosc = nowyPunkt.magnitude();

	for (std::list<Punkt2d>::iterator iter = bufor.begin(); iter != bufor.end(); )
	{
		if ((*iter).magnitude() > odleglosc)
			iter++;
		else
		{
			bufor.insert(iter, nowyPunkt);
			break;
		}
	}
}

Punkt2d Bufor2d::getNext()
{
	if (iter != bufor.end())
		return *(++iter);
	else
	{
		iter = bufor.begin();
		return *iter;
	}
}