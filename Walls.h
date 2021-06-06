#pragma once

#include "ILayer.h"

class Walls : public ILayer
{
public:
	std::tuple<std::vector<Point>, int> getFigure();
};


