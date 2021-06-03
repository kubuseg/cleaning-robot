#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <typeinfo>
using namespace std;

template <typename T, size_t lt, typename U = void, size_t lu = 0>
class Module
{
private:
	//T arrT[Lt];
	//U arrU[Lu];
public:
	/*Module() {};
	Module(T arrTT[lt])
	{
		size_t n = 0;
		for (auto& element : arrT)
			element = arrTT[n++];
	}*/
	if (typeid(U) != void) {
		virtual void setArgs(const T t[lt], const U u[lu]) = 0;
		virtual U* getArrgsU() const = 0;
		virtual void setArgs(const U u[lu]) = 0;
	}
	virtual void setArgs(const T t[lt]) = 0;
	virtual T* getArrgsT() const = 0;

};

class RoadSet : Module<vector<pair<double, double>>, 1>
{
private:
	vector<pair<double, double>> points;
public:
	RoadSet();
};
