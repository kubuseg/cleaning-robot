#include <iostream>
#include "Trace.h"
#include <vector>
#include <tuple>

using namespace std;

typedef pair<int, int> point_t;

Trace::Trace()
{
    amount_of_points = 0;
}

Trace::Trace(vector<point_t> a)
{
    amount_of_points = a.size();
    points = a;
}

float Trace::GetLenght()
{
    float lenght = 0;
    if (points.size() >= 2)
    {
        for (int i = 0; i <= points.size() - 2; ++i)
        {
            int x1 = points[i].first;
            int y1 = points[i].second;
            int x2 = points[i + 1].first;
            int y2 = points[i + 1].second;
            lenght += sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
        }
    }
    return lenght;
}

vector<point_t> Trace::GetPoints()
{
    return points;
}

void Trace::AddPoint(int x, int y)
{
    amount_of_points++;
    points.push_back(make_pair(x, y));
}

void Trace::DeleteLastPoint()
{
    amount_of_points--;
    points.pop_back();
}


int Trace::GetAmountOfPoints() const
{
    return amount_of_points;
}