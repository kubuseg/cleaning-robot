#pragma once
#include <iostream>
#include <vector>
#include "Trace.h"
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

enum class Side { Left, Right, Up, Down };

const size_t columns = 16, rows = 10;

class DrawnMap {
private:
	int size_x;
	int size_y;
	int** Map;
public:
	RenderWindow my_window;
	DrawnMap(int size_x, int size_y, string name_window); 
	~DrawnMap();

	void setMap(int** NewMap);
	void setValue(int x, int y, int value);
	void printMap();
	void drawObstacles();
	void drawTrace(Trace& coord_for_draw);
	void drawCircle(int& x, int& y);
	void moving(int& x, int& y, Trace& coord_for_draw, Side& si);
	void loop(int& x, int& y, Trace& coord_for_draw);
};