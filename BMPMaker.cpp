
#include <iostream>
#include<tuple>

#include "Picture.h"
#include "Room.h"
#include "Walls.h"
#include "Robot.h"

int main()
{
	Picture picture;
	Room room;
	Walls walls;
	Robot robot;

	picture.addLayer(&room, 0);
	picture.addLayer(&walls, 1);
	picture.addLayer(&robot, 2);

	bool state;
	std::tuple<ILayer*, bool> layer = picture.getLayer(0);
	std::tuple<std::vector<Point>, int> points = std::get<0>(layer)->getFigure();
	for (int j = 0; j < std::get<1>(points); j++)
	{
		Point point = std::get<0>(points)[0];
		std::cout << "x: " << std::uint16_t(std::get<0>(points)[j].x) << " y: " << std::uint16_t(std::get<0>(points)[j].y) << " \n";
	}

	system("pause");
}
