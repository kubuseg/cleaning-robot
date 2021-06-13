#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <array>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <stdexcept>

enum class Direction
{
	Right, Left, Up, Down, Unknown
};

struct Point
{
	size_t x, y;
	inline bool operator!=(const Point& p) 
	{ 
		return (x != p.x || y != p.y); 
	}
	inline bool operator==(const Point& p)
	{
		return (x == p.x && y == p.y);
	}
};

static std::vector<std::pair<Point, Point>> Obstacles;

constexpr size_t COLUMNS = 11, ROWS = 13;

using array = std::array<std::array<int, COLUMNS>, ROWS>;

void addWalls(array& map)
{
	const size_t rows = map.size();
	const size_t columns = map[0].size();

	for (size_t x = 0; x < columns; ++x) {
		map[0][x] = 1;
		map[rows - 1][x] = 1;
	}
	for (size_t y = 1; y < rows-1; ++y) {
		map[y][0] = 1;
		map[y][columns - 1] = 1;
	}
}

void addObstacle(const size_t x1, const size_t y1, const size_t x2, const size_t y2, array& map)
{
	Point p1 = { x1, y1 };
	Point p2 = { x2, y2 };
	Obstacles.push_back(std::make_pair(p1, p2));
	const size_t rows = map.size();
	const size_t columns = map[0].size();
	if (y1 >= y2 || x1 >= x2 || x2 > columns - 1 || y2 > rows - 1)
		throw std::invalid_argument("Invalid coordinates");
	for (size_t i = y1; i < y2; ++i)
	{
		for (size_t j = x1; j < x2; ++j)
		{
			map[i][j] = 1;
		}
	}
}

Point step(size_t x0, size_t y0, Direction dir) noexcept {
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

bool allCleaned(const array& map) noexcept {
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
	const size_t rows = map.size();
	const size_t columns = map[0].size();
	/*if (x==0 || x==columns-1 || y == 0 || y == rows-1)
		throw std::invalid_argument("Robot is on the Wall");*/
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
		content = map[y][x + 1];
		break;
	case Direction::Down:
		content = map[y][x - 1];
		break;
	}
	return content;
}

int checkLeftSide(const size_t x, const size_t y, const Direction dir, const array& map)
{
	const size_t rows = map.size();
	const size_t columns = map[0].size();
	/*if (x == 0 || x == columns - 1 || y == 0 || y == rows - 1)
		throw std::invalid_argument("Robot is on the Wall");*/
	int content = 0;
	switch (dir)
	{
	case Direction::Right:
		content = map[y - 1][x];
		break;
	case Direction::Left:
		content = map[y + 1][x];
		break;
	case Direction::Up:
		content = map[y][x - 1];
		break;
	case Direction::Down:
		content = map[y][x + 1];
		break;
	}
	return content;
}

Direction newDirection(const size_t x, const size_t y, const array& map)
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

Direction newDirectionExeption(const size_t x, const size_t y, const array& map)
{
	if (map[y][x + 1] != 1 && checkRightSide(x + 1, y, Direction::Right, map) == 1)
		return Direction::Right;
	else if (map[y][x - 1] != 1 && checkRightSide(x - 1, y, Direction::Left, map) == 1)
		return Direction::Left;
	else if (map[y - 1][x] != 1 && checkRightSide(x, y - 1, Direction::Up, map) == 1)
		return Direction::Up;
	else if (map[y + 1][x] != 1 && checkRightSide(x, y + 1, Direction::Down, map) == 1)
		return Direction::Down;
	else
		return Direction::Unknown;
}

Direction newDirectionExeptionLeft(const size_t x, const size_t y, const array& map)
{
	if (map[y][x + 1] != 1 && checkLeftSide(x + 1, y, Direction::Right, map) == 1)
		return Direction::Right;
	else if (map[y][x - 1] != 1 && checkLeftSide(x - 1, y, Direction::Left, map) == 1)
		return Direction::Left;
	else if (map[y - 1][x] != 1 && checkLeftSide(x, y - 1, Direction::Up, map) == 1)
		return Direction::Up;
	else if (map[y + 1][x] != 1 && checkLeftSide(x, y + 1, Direction::Down, map) == 1)
		return Direction::Down;
	else
		return Direction::Unknown;
}

double lineInX(const int x, const std::pair<double, double> line)
{
	auto [a, b] = line;
	return a * (double)x + b;
}

std::pair<double, double> line(const int x1, const int y1, const int x2, const int y2)
{
	double dy = (double)y2 - (double)y1; double dx = (double)x2 - (double)x1;
	double a = dy / dx;
	double b = (double)y1 - a * (double)x1;
	return std::make_pair(a, b);
}

bool lineGoesThroughtArea(const int x, const int y, const std::pair<double, double> line)
{
	auto [a, b] = line;
	if ((y <= lineInX(x, line) && lineInX(x, line) < (double)y + 1) ||
		(y <= lineInX(x + 1, line) && lineInX(x + 1, line) < (double)y + 1) ||
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
			for (int y = y1; y <= y2; ++y)
			{
				for (int x = x1; x <= x2; ++x)
				{
					if (lineGoesThroughtArea(x, y, l))
					{
						Point p = { (size_t)x, (size_t)y };
						road.push_back(p);
					}
				}
			}
		}
		else
		{
			for (int y = y1; y >= y2; --y)
			{
				for (int x = x1; x <= x2; ++x)
				{
					if (lineGoesThroughtArea(x, y, l))
					{
						Point p = { (size_t)x, (size_t)y };
						road.push_back(p);
					}
				}
			}
		}
	}
	else if (x1 > x2)
	{
		if (y1 < y2)
		{
			for (int y = y1; y <= y2; ++y)
			{
				for (int x = x1; x >= x2; --x)
				{
					if (lineGoesThroughtArea(x, y, l))
					{
						Point p = { (size_t)x, (size_t)y };
						road.push_back(p);
					}
				}
			}
		}
		else
		{
			for (int y = y1; y >= y2; --y)
			{
				for (int x = x1; x >= x2; --x)
				{
					if (lineGoesThroughtArea(x, y, l))
					{
						Point p = { (size_t)x, (size_t)y };
						road.push_back(p);
					}
				}
			}
		}
	}
	else
	{
		if (y1 > y2)
		{
			for (int y = y1; y >= y2; --y)
			{
				Point p = { (size_t)x1, (size_t)y };
				road.push_back(p);
			}
		}
		else {
			for (int y = y1; y <= y2; ++y)
			{
				Point p = { (size_t)x1, (size_t)y };
				road.push_back(p);
			}
		}
	}
	return road;
}

void showRoad(std::vector<Point> steps, const array& map)
{
	array nMap = {};
	auto rows = map.size();
	auto columns = map[0].size();
	__int64 w = std::to_string(steps.size()).length();
	int n = 0;
	for (const auto& step : steps) {
		nMap[step.y][step.x] = ++n;
	}
	for (size_t y = 0; y < rows; ++y)
	{
		for (size_t x = 0; x < columns; ++x)
		{

			if (map[y][x] == 1) {
				std::cout << std::setfill('|') << std::setw(w + 1) << " ";
				continue;
			}
			std::cout << std::setfill('0') << std::setw(w) << nMap[y][x] << " ";
		}
		std::cout << std::endl;
	}
}

bool allSidesUnavailable(const size_t x1, const size_t y1, const array& map)
{
	if (map[y1][x1 - 1] == 0 || map[y1][x1 + 1] == 0 || map[y1 + 1][x1] == 0 || map[y1 - 1][x1] == 0)
		return false;
	else
		return true;
}

double distance(Point p1, Point p2)
{
	double dx = (double)p1.x - (double)p2.x;
	double dy = (double)p1.y - (double)p2.y;
	return sqrt(std::pow(dx, 2) + std::pow(dy, 2));
}

Point findNearestZero(const size_t x1, const size_t y1, const array& map)
{
	auto rows = map.size();
	auto columns = map[0].size();
	Point p1 = { x1, y1 }, bottomRight = { columns - 1, rows - 1 }, upperLeft = {0, 0};
	double minDis = distance(upperLeft, bottomRight), newDis;
	Point nearestPt = p1;
	Point pt;
	for (size_t y = 0; y < rows; ++y)
	{
		for (size_t x = 0; x < columns; ++x)
		{
			if (map[y][x] == 0)
			{
				pt = { x, y };
				newDis = distance(p1, pt);
				if (newDis < minDis)
				{
					minDis = newDis;
					nearestPt = pt;
				}
			}
		}
	}
	return nearestPt;
}

std::pair<Direction, Direction> newDirectionTwoTimes(const size_t x1, const size_t y1, const array& map)
{
	Direction newDir = Direction::Unknown, newDir2 = Direction::Unknown;
	if (map[y1][x1 + 1] == 0) {
		newDir2 = newDirection(x1 + 1, y1, map);
		if (newDir2 != Direction::Unknown)
			return std::make_pair(Direction::Right, newDir2);
	}
	if (map[y1][x1 - 1] == 0) {
		newDir2 = newDirection(x1 - 1, y1, map);
		if (newDir2 != Direction::Unknown)
			return std::make_pair(Direction::Left, newDir2);
	}
	if (map[y1 - 1][x1] == 0) {
		newDir2 = newDirection(x1, y1 - 1, map);
		if (newDir2 != Direction::Unknown)
			return std::make_pair(Direction::Up, newDir2);
	}
	if (map[y1 + 1][x1] == 0) {
		newDir2 = newDirection(x1, y1 + 1, map);
		if (newDir2 != Direction::Unknown)
			return std::make_pair(Direction::Down, newDir2);
	}
	return std::make_pair(newDir, newDir2);
}

std::pair<Direction, Direction> newDirectionTwoTimesExeption(const size_t x1, const size_t y1, const array& map)
{
	Direction newDir = Direction::Unknown, newDir2 = Direction::Unknown;
	if (map[y1][x1 + 1] != 1) {
		newDir2 = newDirectionExeption(x1 + 1, y1, map);
		if (newDir2 != Direction::Unknown)
			return std::make_pair(Direction::Right, newDir2);
	}
	if (map[y1][x1 - 1] != 1) {
		newDir2 = newDirectionExeption(x1 - 1, y1, map);
		if (newDir2 != Direction::Unknown)
			return std::make_pair(Direction::Left, newDir2);
	}
	if (map[y1 - 1][x1] != 1) {
		newDir2 = newDirectionExeption(x1, y1 - 1, map);
		if (newDir2 != Direction::Unknown)
			return std::make_pair(Direction::Up, newDir2);
	}
	if (map[y1 + 1][x1] != 1) {
		newDir2 = newDirectionExeption(x1, y1 + 1, map);
		if (newDir2 != Direction::Unknown)
			return std::make_pair(Direction::Down, newDir2);
	}
	return std::make_pair(newDir, newDir2);
}

std::pair<Direction, Direction> newDirectionTwoTimesExeptionLeft(const size_t x1, const size_t y1, const array& map)
{
	Direction newDir = Direction::Unknown, newDir2 = Direction::Unknown;
	if (map[y1][x1 + 1] != 1) {
		newDir2 = newDirectionExeptionLeft(x1 + 1, y1, map);
		if (newDir2 != Direction::Unknown)
			return std::make_pair(Direction::Right, newDir2);
	}
	if (map[y1][x1 - 1] != 1) {
		newDir2 = newDirectionExeptionLeft(x1 - 1, y1, map);
		if (newDir2 != Direction::Unknown)
			return std::make_pair(Direction::Left, newDir2);
	}
	if (map[y1 - 1][x1] != 1) {
		newDir2 = newDirectionExeptionLeft(x1, y1 - 1, map);
		if (newDir2 != Direction::Unknown)
			return std::make_pair(Direction::Up, newDir2);
	}
	if (map[y1 + 1][x1] != 1) {
		newDir2 = newDirectionExeptionLeft(x1, y1 + 1, map);
		if (newDir2 != Direction::Unknown)
			return std::make_pair(Direction::Down, newDir2);
	}
	return std::make_pair(newDir, newDir2);
}

std::vector<Point> avoidObstacleFromRight(const size_t x1, const size_t y1, std::vector<Point> orginalRoad, const array& map)
{
	std::vector<Point> roadFromRightSide;
	Point pt = { x1 , y1 }, nextPt = {};
	int nextPtRightSide = 2, nextPtContent = 1;
	Direction dir = Direction::Unknown;

	while (std::find(orginalRoad.begin(), orginalRoad.end(), pt) == orginalRoad.end())
	{
		if (nextPtRightSide == 1 && nextPtContent == 2)
		{
			pt = nextPt;
			roadFromRightSide.push_back(pt);
			nextPt = step(pt.x, pt.y, dir);
			nextPtContent = map[nextPt.y][nextPt.x];
			nextPtRightSide = checkRightSide(nextPt.x, nextPt.y, dir, map);
		}
		else
		{
			Direction newDir = newDirectionExeption(pt.x, pt.y, map);
			if (newDir != Direction::Unknown)
			{
				pt = step(pt.x, pt.y, newDir);
				roadFromRightSide.push_back(pt);
				dir = newDir;
				nextPt = step(pt.x, pt.y, dir);
				nextPtContent = map[nextPt.y][nextPt.x];
				nextPtRightSide = checkRightSide(nextPt.x, nextPt.y, dir, map);
			}
			else if (nextPtContent == 2)
			{
				pt = nextPt;
				roadFromRightSide.push_back(pt);
				nextPt = step(pt.x, pt.y, dir);
				nextPtContent = map[nextPt.y][nextPt.x];
				nextPtRightSide = checkRightSide(nextPt.x, nextPt.y, dir, map);
			}
			else if (newDirectionTwoTimesExeption(pt.x, pt.y, map).first != Direction::Unknown)
			{
				auto[newDir, newDir2] = newDirectionTwoTimesExeption(pt.x, pt.y, map);
				pt = step(pt.x, pt.y, newDir);
				roadFromRightSide.push_back(pt);
				dir = newDir2;
				nextPt = step(pt.x, pt.y, dir);
				nextPtContent = map[nextPt.y][nextPt.x];
				nextPtRightSide = checkRightSide(nextPt.x, nextPt.y, dir, map);
			}
		}
	}
	return roadFromRightSide;
}

std::vector<Point> avoidObstacleFromLeft(const size_t x1, const size_t y1, std::vector<Point> orginalRoad, const array& map)
{
	std::vector<Point> roadFromLeftSide;
	Point pt = { x1 , y1 }, nextPt = {};
	int nextPtLeftSide = 0, nextPtContent = 1;
	Direction dir = Direction::Unknown;
	
	while (std::find(orginalRoad.begin(), orginalRoad.end(), pt) == orginalRoad.end())
	{
		if (nextPtLeftSide == 1 && nextPtContent == 2)
		{
			pt = nextPt;
			roadFromLeftSide.push_back(pt);
			nextPt = step(pt.x, pt.y, dir);
			nextPtContent = map[nextPt.y][nextPt.x];
			nextPtLeftSide = checkLeftSide(nextPt.x, nextPt.y, dir, map);
		}
		else
		{
			Direction newDir = newDirectionExeptionLeft(pt.x, pt.y, map);
			if (newDir != Direction::Unknown)
			{
				pt = step(pt.x, pt.y, newDir);
				roadFromLeftSide.push_back(pt);
				dir = newDir;
				nextPt = step(pt.x, pt.y, dir);
				nextPtContent = map[nextPt.y][nextPt.x];
				nextPtLeftSide = checkLeftSide(nextPt.x, nextPt.y, dir, map);
			}
			else if (nextPtContent == 2)
			{
				pt = nextPt;
				roadFromLeftSide.push_back(pt);
				nextPt = step(pt.x, pt.y, dir);
				nextPtContent = map[nextPt.y][nextPt.x];
				nextPtLeftSide = checkLeftSide(nextPt.x, nextPt.y, dir, map);
			}
			else if (newDirectionTwoTimesExeptionLeft(pt.x, pt.y, map).first != Direction::Unknown)
			{
				auto [newDir, newDir2] = newDirectionTwoTimesExeptionLeft(pt.x, pt.y, map);
				pt = step(pt.x, pt.y, newDir);
				roadFromLeftSide.push_back(pt);
				dir = newDir2;
				nextPt = step(pt.x, pt.y, dir);
				nextPtContent = map[nextPt.y][nextPt.x];
				nextPtLeftSide = checkLeftSide(nextPt.x, nextPt.y, dir, map);
			}
		}
	}
	return roadFromLeftSide;
}

std::vector<Point> avoidObstacle(const size_t x1, const size_t y1, std::vector<Point> orginalRoad, const array& map)
{   //Próbuję ominąć z 2 stron i patrze która droga jest krótsza
	std::vector<Point> roadFromRightSide = avoidObstacleFromRight(x1, y1, orginalRoad, map);
	std::vector<Point> roadFromLeftSide = avoidObstacleFromLeft(x1, y1, orginalRoad, map);
	if (roadFromLeftSide.size() < roadFromRightSide.size())
		return roadFromLeftSide;
	else 
		return roadFromRightSide;
}

std::vector<Point> road(const size_t x0, const size_t y0, array& map)
{
	Point pt = { x0, y0 };
	std::vector<Point> steps = { pt };
	map[pt.y][pt.x] = 2;
	Direction dir = Direction::Down;
	Point nextPt = step(pt.x, pt.y, dir);
	int nextPtContent = map[nextPt.y][nextPt.x];
	int nextPtRightSide = checkRightSide(nextPt.x, nextPt.y, dir, map);
	while (!allCleaned(map))
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
			Direction newDir = newDirection(pt.x, pt.y, map);
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
			else if (nextPtContent == 0)
			{
				pt = nextPt;
				map[pt.y][pt.x] = 2;
				steps.push_back(pt);
				nextPt = step(pt.x, pt.y, dir);
				nextPtContent = map[nextPt.y][nextPt.x];
				nextPtRightSide = checkRightSide(nextPt.x, nextPt.y, dir, map);
			}
			else if (newDirectionTwoTimes(pt.x, pt.y, map).first != Direction::Unknown)
			{
				auto[newDir, newDirV2] = newDirectionTwoTimes(pt.x, pt.y, map);
				pt = step(pt.x, pt.y, newDir);
				map[pt.y][pt.x] = 2;
				steps.push_back(pt);
				dir = newDirV2;
				nextPt = step(pt.x, pt.y, dir);
				nextPtContent = map[nextPt.y][nextPt.x];
				nextPtRightSide = checkRightSide(nextPt.x, nextPt.y, dir, map);
			}
			else if (allSidesUnavailable(pt.x, pt.y, map))
			{
				Point nearestZero = findNearestZero(pt.x, pt.y, map);
				std::vector<Point> roadBetweenPoints = moveBetweenPoints(pt.x, pt.y, nearestZero.x, nearestZero.y, map);
				size_t roadStepNum = 1;
				while (steps.back() != nearestZero)
				{
					nextPt = roadBetweenPoints[roadStepNum];	
					if (map[nextPt.y][nextPt.x] != 1)
					{
						pt = nextPt;
						steps.push_back(pt);
						roadStepNum++;
					}
					else
					{
						std::vector<Point> roadFromPtToZero;
						for (size_t i = roadStepNum + 1; i < roadBetweenPoints.size(); i++)
							roadFromPtToZero.push_back(roadBetweenPoints[i]);
						std::vector<Point> avoidenceRoad = avoidObstacle(pt.x, pt.y, roadFromPtToZero, map);
						for (const auto& point : avoidenceRoad)
							steps.push_back(point);
						std::vector<Point>::iterator it = std::find(roadBetweenPoints.begin(), roadBetweenPoints.end(), steps.back());
						roadStepNum = std::distance(roadBetweenPoints.begin(), it) + 1;
					}
				}
				pt = steps.back();
				map[pt.y][pt.x] = 2;
			}
		}
	}
	return steps;
}

int main()
{
	array map = {};
	addWalls(map);
	try 
	{
		addObstacle(0, 4, 5, 5, map);
		addObstacle(8, 3, 9, 4, map);
		addObstacle(6, 8, 7, 11, map);
		addObstacle(0, 8, 3, 9, map);
	}
	catch (std::invalid_argument& i)
	{
		std::cerr << i.what()<<std::endl;
	}
	
	std::vector<Point> steps = road(1, 1, map);
	showRoad(steps, map);
	/*for (size_t y = 0; y < ROWS; ++y)
	{
		for (size_t x = 0; x < COLUMNS; ++x)
		{
			std::cout <<" "<< map[y][x];
		}
		std::cout << std::endl;
	}*/
}
