#pragma once
#include "Map.h"
#include<vector>
#include<iostream>
#include <tuple>
using namespace std;

enum class Direction { Left, Right, Up, Down, Unknown };

struct Point { size_t x, y; };

class Track
{
private:
    vector<Point> points;
    int amount_of_points;
public:
    Track(vector<Point> a);

    vector<Point> getPoints();
    int getAmountOfPoints();
    void addPoint(Point p);
    void deleteLastPoint();
    bool operator==(vector<Point>& tr2);
    Point step(size_t x0, size_t y0, Direction dir);
    int checkRightSide(const size_t x, const size_t y, const Direction dir, Map* map2d);
    Direction checkSides(const size_t x, const size_t y, Map* map2d);
};

bool operator==(vector<Point>& tr1, vector<Point>& tr2);
bool operator==(Point& p1, Point& p2);