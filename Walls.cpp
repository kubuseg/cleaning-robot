#include "Walls.h"
#include <tuple>

std::tuple<std::vector<Point>, int> Walls::getFigure() {
	std::vector<Point> robotFigure;
	int len = 0;

	for (int i = 1; i < 99; i++)
	{
		for (int j = 1; j < 99; j++)
		{
			if ( (i == 50 || j == 50) && (i < 45 || i > 55 || j < 45 || j > 55) || ( i  == 50 && j == 50 ) )
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

