#pragma once
#include<vector>
#include<iostream>
#include <tuple>
using namespace std;
typedef pair<int, int> point_t;

class Trace
{
private:
    int amount_of_points;

    vector<point_t> points;
public:
    Trace();

    Trace(vector<point_t> a);

    float getLenght();
    vector<point_t> getPoints();
    void addPoint(int x, int y);
    void deleteLastPoint();
    int getAmountOfPoints() const;
    bool operator==(vector<point_t>& tr2);
};
