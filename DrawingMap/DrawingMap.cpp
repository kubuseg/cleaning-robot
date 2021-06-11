#include "DrawnMap.h"

DrawnMap::DrawnMap(Map* map2d, string name_window){
	this->size_x = map2d->getColumns();
	this->size_y = map2d->getRows();
	this->map2d = map2d;
	my_window.create(VideoMode(size_x * 10, size_y * 10), name_window);
}

void DrawnMap::setValue(int x, int y, int value)
{
	map2d->setValue(x, y, value);
}

void DrawnMap::printMap() {
	for (size_t row = 0; row < size_y; ++row) {
		for (size_t column = 0; column < size_x; ++column) {
			cout << map2d->getMap()[row][column] << " ";
		}
		cout << endl;
	}
}

void DrawnMap::drawObstacles() {
	RectangleShape rectangle(Vector2f(10, 10));
	rectangle.setFillColor(Color(175, 180, 240));

	for (size_t row = 0; row < size_y; ++row)
	{
		for (size_t column = 0; column < size_x; ++column)
		{
			if (map2d->getMap()[row][column] == 1)
			{
				rectangle.setPosition(column * 10, row * 10);
				my_window.draw(rectangle);
			}
		}
	}
}

void DrawnMap::drawTrace(Trace& coord_for_draw) {
	CircleShape small_circle(5);
	small_circle.setFillColor(Color(250, 250, 250));
	for (auto item : coord_for_draw.getPoints()) {
		small_circle.setPosition(item.first, item.second);
		my_window.draw(small_circle);
	}
}

void DrawnMap::drawCircle(int& x, int& y) {
	CircleShape circle(5);
	circle.setFillColor(Color(250, 0, 250));
	circle.setPosition(x, y);
	my_window.draw(circle);
}

void DrawnMap::moving(int& x, int& y, Trace& coord_for_draw, Direction& di) {
	int adder_x = 0, adder_y = 0, d_x = 0, d_y = 0, temp_x = x, temp_y = y, for_if = 0;

	switch (di) {
	case Direction::Left: x -= 1; d_y = 1; for_if = y; break;
	case Direction::Right: x += 1; d_y = 1; adder_x = (x % 10 == 0) ? 0 : 1; for_if = y; break;
	case Direction::Up: y -= 1; d_x = 1; for_if = x; break;
	case Direction::Down: y += 1; d_x = 1; adder_y = (y % 10 == 0) ? 0 : 1; for_if = x; break;
	}

	if (for_if % 10 == 0) {
		if (map2d->getMap()[y / 10 + adder_y][x / 10 + adder_x] != 1) {
			map2d->getMap()[y / 10 + adder_y][x / 10 + adder_x] = 2;
			coord_for_draw.addPoint(x, y);
		}
		else { x = temp_x; y = temp_y; }

	}
	else if (for_if % 10 != 0) {
		int f = map2d->getMap()[y / 10 + adder_y][x / 10 + adder_x];
		int s = map2d->getMap()[y / 10 + d_y + adder_y][x / 10 + d_x + adder_x];
		if (f != 1 && s != 1) {
			map2d->getMap()[y / 10 + adder_y][x / 10 + adder_x] = 2;
			map2d->getMap()[y / 10 + d_y + adder_y][x / 10 + d_x + adder_x] = 2;
			coord_for_draw.addPoint(x, y);
		}
		else { x = temp_x; y = temp_y; }
	}
}

void DrawnMap::loop(int& x, int& y, Trace& coord_for_draw) {
	while (my_window.isOpen())
	{
		Event event;
		while (my_window.pollEvent(event))
		{

			if (event.type == Event::Closed) {
				printMap();
				my_window.close();
			}
		}
		if (event.type == Event::KeyPressed) {
			if (event.key.code == Keyboard::Left) {
				Direction direct = Direction::Left;
				moving(x, y, coord_for_draw, direct);
			}

			else if (event.key.code == Keyboard::Right) {
				Direction direct = Direction::Right;
				moving(x, y, coord_for_draw, direct);
			}

			else if (event.key.code == Keyboard::Up) {
				Direction direct = Direction::Up;
				moving(x, y, coord_for_draw, direct);
			}

			else if (event.key.code == Keyboard::Down) {
				Direction direct = Direction::Down;
				moving(x, y, coord_for_draw, direct);
			}
		}
		my_window.clear(Color(100, 100, 100));
		drawObstacles();
		drawTrace(coord_for_draw);
		drawCircle(x, y);
		my_window.display();
	}
}

int main()
{
	vector<vector<int>> map2d = { 
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}

	};

	Trace coord_for_draw({ {10, 10} });

	int started_x = 10, started_y = 10; map2d[started_y / 10][started_x / 10] = 2;
	int x = started_x, y = started_y;



	Map m1(map2d);
	m1.addWalls();
	m1.addObstacle(2, 3, 9, 3);
	DrawnMap dm(&m1, "Window1");
	dm.loop(x, y, coord_for_draw);
}