#include "Trace.h"
#include "Map.h"
#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;

enum class Direction { Left, Right, Up, Down };

//const size_t columns = 16, rows = 10;

class DrawnMap {
private:
	int size_x;
	int size_y;
	Map* map2d;
public:
	RenderWindow my_window;
	DrawnMap(Map* map2d, string name_window);

	void setValue(int x, int y, int value);
	void printMap();
	void drawObstacles();
	void drawTrace(Trace& coord_for_draw);
	void drawCircle(int& x, int& y);
	void moving(int& x, int& y, Trace& coord_for_draw, Direction& di);
	void loop(int& x, int& y, Trace& coord_for_draw);
};