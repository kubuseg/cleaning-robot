#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

const size_t columns = 16, rows = 10;

void printMap(int(&map)[rows][columns]) {
	for (size_t row = 0; row < rows; ++row) {
		for (size_t column = 0; column < columns; ++column) {
			cout << map[row][column] << " ";
		}
		cout << endl;
	}
}

void drawObstacles(RenderWindow& window, int(&map)[rows][columns]) {
	RectangleShape rectangle(Vector2f(10, 10));
	rectangle.setFillColor(Color(175, 180, 240));

	for (size_t row = 0; row < rows; ++row)
	{
		for (size_t column = 0; column < columns; ++column)
		{
			if (map[row][column] == 1)
			{
				rectangle.setPosition(column * 10, row * 10);
				window.draw(rectangle);
			}
		}
	}
}

void drawTrace(RenderWindow& window, const vector<pair<int, int>>& coord_for_draw) {
	CircleShape small_circle(5);
	small_circle.setFillColor(Color(250, 250, 250));
	for (auto item : coord_for_draw) {
		small_circle.setPosition(item.first, item.second);
		window.draw(small_circle);
	}
}

void drawCircle(RenderWindow& window, int& x, int& y) {
	CircleShape circle(5);
	circle.setFillColor(Color(250, 0, 250));
	circle.setPosition(x, y);
	window.draw(circle);
}

void updateVec(vector<pair<int, int>>& coord_for_draw, int x, int y) {
	coord_for_draw.push_back(make_pair(x, y));
}

void moving(int(&map)[rows][columns], int& x, int& y, vector<pair<int, int>>& coord_for_draw, int side) {
	int adder_x = 0, adder_y = 0, d_x = 0, d_y = 0, temp_x = x, temp_y = y, for_if = 0;
	
	switch (side) {
	case 1: x -= 1; d_y = 1; for_if = y; break;
	case 2: x += 1; d_y = 1; adder_x = (x % 10 == 0) ? 0 : 1; for_if = y; break;
	case 3: y -= 1; d_x = 1; for_if = x; break;
	case 4: y += 1; d_x = 1; adder_y = (y % 10 == 0) ? 0 : 1; for_if = x; break;
	}

	if (for_if % 10 == 0) {
		if (map[y / 10 + adder_y][x / 10 + adder_x] != 1) {
			map[y / 10 + adder_y][x / 10 + adder_x] = 2;
			updateVec(coord_for_draw, x, y);
		}
		else { x = temp_x; y = temp_y; }

	}
	else if (for_if % 10 != 0) {
		int f = map[y / 10 + adder_y][x / 10 + adder_x];
		int s = map[y / 10 + d_y + adder_y][x / 10 + d_x + adder_x];
		if (f != 1 && s != 1) {
			map[y / 10 + adder_y][x / 10 + adder_x] = 2;
			map[y / 10 + d_y + adder_y][x / 10 + d_x + adder_x] = 2;
			updateVec(coord_for_draw, x, y);
		}
		else { x = temp_x; y = temp_y; }
	}
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

	vector<pair<int, int>> coord_for_draw = { {10, 10} };

	RenderWindow window(VideoMode(160, 100), "Room");
	int started_x = 10, started_y = 10; map[started_y / 10][started_x / 10] = 2;
	int x = started_x, y = started_y;
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				window.close();
				printMap(map);
			}
			if (event.type == Event::KeyPressed) {


				if (event.key.code == Keyboard::Left) {
					moving(map, x, y, coord_for_draw, 1);
				}

				if (event.key.code == Keyboard::Right) {
					moving(map, x, y, coord_for_draw, 2);
				}

				else if (event.key.code == Keyboard::Up) {
					moving(map, x, y, coord_for_draw, 3);
				}

				else if (event.key.code == Keyboard::Down) {
					moving(map, x, y, coord_for_draw, 4);
				}

			}
		}

		window.clear(Color(100, 100, 100));

		drawObstacles(window, map);
		
		drawTrace(window, coord_for_draw);

		drawCircle(window, x, y);

		window.display();
	}

	return 0;
}