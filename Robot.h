#pragma once

#include "ILayer.h"

class Robot : public ILayer
{
public:
	std::tuple<std::vector<Point>, int> getFigure();
};

