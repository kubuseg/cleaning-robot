#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

enum Side {
	Left,
	Right,
	Up,
	Down
};

const size_t columns = 16, rows = 10;

class DrawnMap {
private:
	int size_x;
	int size_y;
	int** Map;
public:
	RenderWindow my_window;
	DrawnMap(int size_x, int size_y, string name_window); 
	//~DrawnMap();

	void setMap(int** NewMap);
	void setValue(int x, int y, int value);
	void printMap();
	void drawObstacles();
	void drawTrace(const vector<pair<int, int>>& coord_for_draw);
	void drawCircle(int& x, int& y);
	void moving(int& x, int& y, vector<pair<int, int>>& coord_for_draw, Side& si);
	void loop(int& x, int& y, vector<pair<int, int>>& coord_for_draw);
};