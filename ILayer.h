#pragma once

#include <chrono>
#include <vector>
#include "Point.h"

#define OUT

class ILayer
{
private:
	std::chrono::system_clock::time_point modyficationDate = updateModyficationTime();
	bool activeState = true;
	Point position;

public:
	virtual std::tuple<std::vector<Point>, int> getFigure() = 0;
	std::chrono::system_clock::time_point updateModyficationTime();
	void setActiveState(bool);
	bool getActiveState();
	void moveToPoint(uint8_t, uint8_t);
};

