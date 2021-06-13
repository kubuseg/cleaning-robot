#include "Track.h"

Track::Track()
{
    amount_of_points = 0;
}

Track::Track(vector<Point> a)
{
    amount_of_points = a.size();
    points = a;
}

vector<Point> Track::getPoints() const
{
    return points;
}

int Track::getAmountOfPoints() const
{
    return amount_of_points;
}

void Track::addPoint(Point p)
{
    amount_of_points++;
    points.push_back(p);
}

void Track::deleteLastPoint()
{
    amount_of_points--;
    points.pop_back();
}

bool Track::operator==(vector<Point>& tr2)
{
	if (tr2.size() != this->points.size()) return false;
	for (int i = 0; i < this->points.size(); ++i)
		if (tr2[i].x != this->points[i].x || tr2[i].y != this->points[i].y)
			return false;
	return true;
}

Point Track::step(size_t x0, size_t y0, Direction dir) {
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

int Track::checkRightSide(const size_t x, const size_t y, const Direction dir, Map* map2d)
{
	int content = 0;
	switch (dir)
	{
	case Direction::Right:
		content = map2d->getMap()[y + 1][x];
		break;
	case Direction::Left:
		content = map2d->getMap()[y - 1][x];
		break;
	case Direction::Up:
		content = map2d->getMap()[y][x + 1];
		break;
	case Direction::Down:
		content = map2d->getMap()[y][x - 1];
		break;
	}
	return content;
}

Direction Track::checkSides(const size_t x, const size_t y, Map* map2d)
{
	if (map2d->getMap()[y][x + 1] == 0 && checkRightSide(x + 1, y, Direction::Right, map2d))
		return Direction::Right;
	else if (map2d->getMap()[y][x - 1] == 0 && checkRightSide(x - 1, y, Direction::Left, map2d))
		return Direction::Left;
	else if (map2d->getMap()[y - 1][x] == 0 && checkRightSide(x, y - 1, Direction::Up, map2d))
		return Direction::Up;
	else if (map2d->getMap()[y + 1][x] == 0 && checkRightSide(x, y + 1, Direction::Down, map2d))
		return Direction::Down;
	else
		return Direction::Unknown;
}

