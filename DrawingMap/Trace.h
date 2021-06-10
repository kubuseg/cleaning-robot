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

    float GetLenght();

    vector<point_t> GetPoints();

    void AddPoint(int x, int y);

    void DeleteLastPoint();

    int GetAmountOfPoints() const;
};
