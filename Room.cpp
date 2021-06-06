#include "Room.h"
#include <tuple>


std::tuple<std::vector<Point>, int> Room::getFigure() {
	std::vector<Point> robotFigure;
	int len = 0;

	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (i == 0 || i == 99 || j == 0 || j == 99)
			{
				Point pixel;
				pixel.x = i;
				pixel.y = j;
				robotFigure.push_back(pixel);
				len++;
			}
		}
	}
	return std::make_tuple(robotFigure, len);
}

