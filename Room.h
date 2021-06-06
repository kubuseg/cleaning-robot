#pragma once

#include "ILayer.h"

class Room : public ILayer
{
public:
	std::tuple<std::vector<Point>, int> getFigure();
};
