#include "Robot.h"
#include <tuple>

#define LEN 9

std::tuple<std::vector<Point>, int> Robot::getFigure() {
	std::vector<Point> robotFigure;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Point pixel;
			pixel.x = i;
			pixel.y = j;
			robotFigure.push_back(pixel);
		}
	}
	return std::make_tuple(robotFigure, LEN);
}
