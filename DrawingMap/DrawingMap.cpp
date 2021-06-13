#include "DrawnMap.h"

DrawnMap::DrawnMap(Map* map2d, string name) {
	this->size_x = map2d->getColumns();
	this->size_y = map2d->getRows();
	this->map2d = map2d;
	my_window.create(VideoMode(size_x* scale, size_y * scale), name);
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
	RectangleShape rectangle(Vector2f(1*scale,1* scale));
	rectangle.setFillColor(Color(175, 180, 240));

	for (size_t row = 0; row < size_y; ++row)
	{
		for (size_t column = 0; column < size_x; ++column)
		{
			if (map2d->getMap()[row][column] == 1)
			{
				rectangle.setPosition(column * scale, row * scale);
				my_window.draw(rectangle);
			}
		}
	}
}

void DrawnMap::drawTrace(vector<pair<int, int>>& coord_for_draw) {
	RectangleShape small_rectangle(Vector2f(1 * scale, 1 * scale));
	small_rectangle.setFillColor(Color(250, 250, 250));
	for (auto item : coord_for_draw) {
		small_rectangle.setPosition(item.first * scale, item.second * scale);
		my_window.draw(small_rectangle);
	}
}

void DrawnMap::drawCircle(int& x, int& y) {
	CircleShape circle(0.5 * scale);
	circle.setFillColor(Color(250, 0, 250));
	circle.setPosition(x * scale, y * scale);
	my_window.draw(circle);
}

Track DrawnMap::road(const size_t x0, const size_t y0, Map* map2d){
	Point pt = { x0, y0 };
	Track steps({ pt });
	map2d->setValue(pt.x, pt.y, 2);
	Direction dir = Direction::Down;
	Point nextPt = steps.step(pt.x, pt.y, dir);
	int nextPtContent = map2d->getMap()[nextPt.y][nextPt.x];
	int nextPtRightSide = steps.checkRightSide(nextPt.x, nextPt.y, dir, map2d);
	while (!map2d->checkIfAllCleaned())
	{
		if (nextPtRightSide && nextPtContent == 0)
		{
			pt = nextPt;
			map2d->setValue(pt.x, pt.y, 2);
			steps.addPoint(pt);
			nextPt = steps.step(pt.x, pt.y, dir);
			nextPtContent = map2d->getMap()[nextPt.y][nextPt.x];
			nextPtRightSide = steps.checkRightSide(nextPt.x, nextPt.y, dir, map2d);
		}
		else
		{
			Direction newDir = steps.checkSides(pt.x, pt.y, map2d);
			if (newDir != Direction::Unknown)
			{
				pt = steps.step(pt.x, pt.y, newDir);
				map2d->setValue(pt.x, pt.y, 2);
				steps.addPoint(pt);
				dir = newDir;
				nextPt = steps.step(pt.x, pt.y, dir);
				nextPtContent = map2d->getMap()[nextPt.y][nextPt.x];
				nextPtRightSide = steps.checkRightSide(nextPt.x, nextPt.y, dir, map2d);
			}
			else if (nextPtContent == 0)
			{
				pt = nextPt;
				map2d->setValue(pt.x, pt.y, 2);
				steps.addPoint(pt);
				nextPt = steps.step(pt.x, pt.y, dir);
				nextPtContent = map2d->getMap()[nextPt.y][nextPt.x];
				nextPtRightSide = steps.checkRightSide(nextPt.x, nextPt.y, dir, map2d);
			}
			else
			{
				break;
			}

		}
	}
	return steps;
}

void DrawnMap::loop(int& x, int& y, vector<pair<int, int>>& coord_for_draw) {
	cout << "size_x rawen " << size_x << ", size_y rawen " << size_y << endl;
	float timer = 0, delay = 0.1;
	Clock clock;
	Track steps = road(x, y, map2d);
	vector<Point> trace = steps.getPoints();
	int i = 0;
	x = trace[i].x;
	y = trace[i].y;
	while (my_window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;
		Event event;
		while (my_window.pollEvent(event))
		{

			if (event.type == Event::Closed) {
				my_window.close();
			}
		}
		if (timer > delay)
		{
			i += 1;
			x = trace[i].x;
			y = trace[i].y;
			coord_for_draw.push_back({ x, y });
			timer = 0;
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
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	};

	cout << map2d.size() <<" " << map2d[0].size();
	size_t started_x = 1, started_y = 1;
	int x = started_x, y = started_y;
	vector<pair<int, int>> coord_for_draw ={ make_pair(started_x, started_y) };


	Map m1(map2d);
	m1.addWalls();
	m1.addObstacle(2, 3, 13, 4);
	m1.addObstacle(25, 15, 27, 37);
	DrawnMap dm(&m1, "Testik");
	dm.loop(x, y, coord_for_draw);
}
