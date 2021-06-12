#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <array>
#include <iomanip>


enum class Direction 
{
	Right, Left, Up, Down, Unknown
};

struct Point
{
	size_t x, y;
};

struct Dir
{
	Direction current, old;
};

static std::vector<std::pair<Point, Point>> Obstacles;

const size_t columns = 24, rows = 16;

using array = std::array<std::array<int, columns>, rows>;

void addWalls(array& map)
{
	auto rows = map.size();
	auto columns = map[0].size();

	for (size_t j = 0; j < columns; ++j) {
		map[0][j] = 1;
		map[rows - 1][j] = 1;
	}
	for (size_t i = 0; i < rows; ++i) {
		map[i][0] = 1;
		map[i][columns - 1] = 1;
	}
}

void addObstacle(const size_t x1, const size_t y1, const size_t x2, const size_t y2, array& map)
{
	Point p1 = { x1, y1 };
	Point p2 = { x2, y2 };
	Obstacles.push_back(std::make_pair(p1, p2));
	for (size_t i = y1; i < y2; ++i)
	{
		for (size_t j = x1; j < x2; ++j)
		{
			map[i][j] = 1;
		}
	}
}

Point step(size_t x0, size_t y0, Direction dir) {
	Point p = {};
	switch (dir) 
	{
	case Direction::Right:
		p = { x0 + 1, y0 };
		break;
	case Direction::Left:
		p = { x0 - 1, y0 };
		break;
	case Direction::Up:
		p = { x0, y0 - 1 };
		break;
	case Direction::Down:
		p = { x0, y0 + 1 };
		break;
	}
	return p;
}

bool allCleaned(const array& map) {
	for (const auto& j : map) {
		for (auto i : j) {
			if (i == 0) {
				return false;
			}
		}
	}
	return true;
}

int checkRightSide(const size_t x, const size_t y, const Direction dir, const array& map)
{
	int content = 0;
	switch (dir)
	{
	case Direction::Right:
		content = map[y + 1][x];
		break;
	case Direction::Left:
		content = map[y - 1][x];
		break;
	case Direction::Up:
		content = map[y][x+1];
		break;
	case Direction::Down:
		content = map[y][x-1];
		break;
	}
	return content;
}

Direction checkSides(const size_t x, const size_t y, const array& map)
{
	if (map[y][x + 1] == 0 && checkRightSide(x + 1, y, Direction::Right, map))
		return Direction::Right;
	else if (map[y][x - 1] == 0 && checkRightSide(x - 1, y, Direction::Left, map))
		return Direction::Left;
	else if (map[y - 1][x] == 0 && checkRightSide(x, y - 1, Direction::Up, map))
		return Direction::Up;
	else if (map[y + 1][x] == 0 && checkRightSide(x, y + 1, Direction::Down, map))
		return Direction::Down;
	else
		return Direction::Unknown;
}

//std::pair<double, double> line(const int x1, const int y1, const int x2, const int y2)
//{
//	double dy = (y2 - y1), dx = (x2 - x1);
//	double a = dy / dx;
//	double ax1 = a * x1;
//	double b = y1 - ax1;
//	return std::make_pair(a, b);
//}

double f(const int x, const std::pair<double, double> line)
{
	auto[a, b] = line;
	return a * (double)x + b;
}

std::pair<double, double> line(const int x1, const int y1, const int x2, const int y2)
{
	// double x1 = (double)(x11+0.5);
	// double y1 = (double)(y11+0.5);
	// double x2 = (double)(x22+0.5);
	// double y2 = (double)(y22+0.5);
	double dy = (double)y2 - (double)y1; double dx = (double)x2 - (double)x1;
	double a = dy / dx;
	double b = (double)y1 - a * (double)x1;
	return std::make_pair(a, b);
}

bool lineGoesThroughtArea(const int x, const int y, const std::pair<double, double> line)
{
	auto[a, b] = line;
	if ((y <= f(x, line) && f(x, line) < (double)y + 1) ||
		(y <= f(x + 1, line) && f(x + 1, line) < (double)y + 1) ||
		(x < (double)((double)y - b) / a && (double)((double)y - b) / a < (double)x + 1) ||
		(x < (double)((double)y + 1 - b) / a && (double)((double)y + 1 - b) / a < (double)x + 1))
		return true;
	else
		return false;
}

std::vector<Point> moveBetweenPoints(const int x1, const int y1, const int x2, const int y2, array& map)
{
	auto l = line(x1, y1, x2, y2);
	std::vector<Point> road;
	if (x1 < x2)
	{
		if (y1 < y2)
		{
			for (int i = y1; i <= y2; ++i)
			{
				for (int j = x1; j <= x2; ++j)
				{
					if (lineGoesThroughtArea(j, i, l))
					{
						Point p = { (size_t)j, (size_t)i };
						road.push_back(p);
					}
				}
			}
		}
		else
		{
			for (int i = y1; i >= y2; --i)
			{
				for (int j = x1; j <= x2; ++j)
				{
					if (lineGoesThroughtArea(j, i, l))
					{
						Point p = { (size_t)j, (size_t)i };
						road.push_back(p);
					}
				}
			}
		}
	}
	else
	{
		if (y1 < y2)
		{
			for (int i = y1; i <= y2; ++i)
			{
				for (int j = x1; j >= x2; --j)
				{
					if (lineGoesThroughtArea(j, i, l))
					{
						Point p = { (size_t)j, (size_t)i };
						road.push_back(p);
					}
				}
			}
		}
		else
		{
			for (int i = y1; i >= y2; --i)
			{
				for (int j = x1; j >= x2; --j)
				{
					if (lineGoesThroughtArea(j, i, l))
					{
						Point p = { (size_t)j, (size_t)i };
						road.push_back(p);
					}
				}
			}
		}
	}
	return road;
}

void showRoad(std::vector<Point> steps, const array& map)
{
	array nMap = {};
	int n = 0;
	__int64 w = std::to_string(((rows - 2) * (columns - 2))).length();
	for (const auto& step : steps) {
		nMap[step.y][step.x] = ++n;
	}
	for (size_t i = 0; i < rows; ++i)
	{
		for (size_t j = 0; j < columns; ++j)
		{
			
			if (map[i][j] == 1) {
				std::cout << std::setfill('|') << std::setw(w+1) << " ";
				continue;
			}
			std::cout << std::setfill('0') << std::setw(w) << nMap[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

std::vector<Point> road(const size_t x0, const size_t y0, array& map)
{
	Point pt = {x0, y0};
	std::vector<Point> steps = { pt };
	map[pt.y][pt.x] = 2;
	Direction dir = Direction::Down;
	Point nextPt = step(pt.x, pt.y, dir);
	int nextPtContent = map[nextPt.y][nextPt.x];
	int nextPtRightSide = checkRightSide(nextPt.x, nextPt.y, dir, map);
	//Dir dir = { dir0, Direction::Right };
	while (!allCleaned(map) /*&& std::size(steps)<65*/ )
	{
		if (nextPtRightSide && nextPtContent == 0)
		{
			pt = nextPt;
			map[pt.y][pt.x] = 2;
			steps.push_back(pt);
			nextPt = step(pt.x, pt.y, dir);
			nextPtContent = map[nextPt.y][nextPt.x];
			nextPtRightSide = checkRightSide(nextPt.x, nextPt.y, dir, map);
		}
		else
		{
			Direction newDir = checkSides(pt.x, pt.y, map);
			if (newDir != Direction::Unknown)
			{
				pt = step(pt.x, pt.y, newDir);
				map[pt.y][pt.x] = 2;
				steps.push_back(pt);
				dir = newDir;
				nextPt = step(pt.x, pt.y, dir);
				nextPtContent = map[nextPt.y][nextPt.x];
				nextPtRightSide = checkRightSide(nextPt.x, nextPt.y, dir, map);
			}
			else if(nextPtContent == 0)
			{
				pt = nextPt;
				map[pt.y][pt.x] = 2;
				steps.push_back(pt);
				nextPt = step(pt.x, pt.y, dir);
				nextPtContent = map[nextPt.y][nextPt.x];
				nextPtRightSide = checkRightSide(nextPt.x, nextPt.y, dir, map);
			}
			else
			{
				break;
			}
		
		}	
	}
	return steps;
}



int main() 
{	
	array map = {};
	addWalls(map);
	addObstacle(0, 6, 11, 7, map);
	addObstacle(10, 7, 11, 11, map);
	addObstacle(8, 10, 11, 11, map);
	std::vector<Point> steps = road(1, 1, map);
	//showRoad(steps, map);
	auto r = moveBetweenPoints(9, 7, 0, 2, map);
	for (const auto& step : r)
	{
		std::cout << " " << step.x << " | " << step.y << std::endl;
	}
	/*for (size_t i = 0; i < rows; ++i)
	{
		for (size_t j = 0; j < columns; ++j)
		{
			std::cout << map[i][j];
		}
		std::cout << std::endl;
	}*/
}