#include "Track.h"
#include "Map.h"
#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;

const int scale = 5;

struct Dir
{
	Direction current, old;
};

class DrawnMap {
private:
	int size_x;
	int size_y;
	Map* map2d;
	
public:
	RenderWindow my_window;
	DrawnMap(Map* map2d, string name);

	void setValue(int x, int y, int value);
	void printMap();
	void drawObstacles();
	void drawTrace(vector<pair<int, int>>& trace);
	void drawCircle(int& x, int& y);
	//void drawBattery();
	Track road(const size_t x0, const size_t y0, Map* map2d);
	void loop(int& x, int& y, vector<pair<int, int>>& coord_for_draw);
};