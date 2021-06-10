#include "DrawnMap.h"

DrawnMap::DrawnMap(int size_x, int size_y, string name_window) {
	my_window.create(VideoMode(size_x * 10, size_y * 10), name_window);
	this->size_x = size_x;
	this->size_y = size_y;
	Map = new int* [size_x];
	for (int i = 0; i < size_x; i++)
	{
		Map[i] = new int[size_y];
		for (int j = 0; j < size_y; j++)
			Map[i][j] = 0;
	}
}

DrawnMap::~DrawnMap() {
	
	for (int i = 0; i < size_x; i++)
	{
		delete[] Map[i];
	}
	delete[]Map;
}

void DrawnMap::setMap(int** NewMap)
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			this->Map[i][j] = NewMap[i][j];
}

void DrawnMap::setValue(int x, int y, int value)
{
	this->Map[x][y] = value;
}

void DrawnMap::printMap() {
	for (size_t row = 0; row < rows; ++row) {
		for (size_t column = 0; column < columns; ++column) {
			cout << Map[row][column] << " ";
		}
		cout << endl;
	}
}

void DrawnMap::drawObstacles(){
	RectangleShape rectangle(Vector2f(10, 10));
	rectangle.setFillColor(Color(175, 180, 240));

	for (size_t row = 0; row < rows; ++row)
	{
		for (size_t column = 0; column < columns; ++column)
		{
			if (Map[row][column] == 1)
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
		if (Map[y / 10 + adder_y][x / 10 + adder_x] != 1) {
			Map[y / 10 + adder_y][x / 10 + adder_x] = 2;
			coord_for_draw.addPoint(x, y);
		}
		else { x = temp_x; y = temp_y; }

	}
	else if (for_if % 10 != 0) {
		int f = Map[y / 10 + adder_y][x / 10 + adder_x];
		int s = Map[y / 10 + d_y + adder_y][x / 10 + d_x + adder_x];
		if (f != 1 && s != 1) {
			Map[y / 10 + adder_y][x / 10 + adder_x] = 2;
			Map[y / 10 + d_y + adder_y][x / 10 + d_x + adder_x] = 2;
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

int** allocateForMap(int(&map)[rows][columns]) {
	int** A = new int* [rows];
	for (int i = 0; i < rows; i++)
	{
		A[i] = new int[columns];
		for (int j = 0; j < columns; j++)
			A[i][j] = map[i][j];
	}
	return A;
}

int main()
{
	int map[rows][columns]= {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	int** double_p_map = allocateForMap(map);

	Trace coord_for_draw({ {10, 10} });

	int started_x = 10, started_y = 10; map[started_y / 10][started_x / 10] = 2;
	int x = started_x, y = started_y;

	DrawnMap dm(columns, rows, "Window1");
	dm.setMap(double_p_map);
	dm.loop(x, y, coord_for_draw);
}