#pragma once
#include<vector>
#include<iostream>
#include <tuple>
using namespace std;
typedef pair<int, int> point_t;

class Polygonal
{
private:
    int amount_of_points;

    vector<point_t> points;
public:
    Polygonal();

    Polygonal(vector<point_t> a);

    float GetLenght();

    point_t GetPoint(int index);

    int GetIndex(point_t point);
    
    void GetPoints();
    
    void AddPoint(point_t point);
    
    void DeleteLastPoint();
    
    void AddLine(vector<point_t> line);
        
    void ChangePoint(point_t point1, point_t point2);

    int GetAmountOfPoints() const;

    bool CheckClosed();

    bool operator==(vector<point_t>& pol2);

    friend ostream& operator<< (ostream& out, const Polygonal& pol);
    friend istream& operator>> (istream& in, Polygonal& pol);
};

ostream& operator<< (ostream& out, const Polygonal& pol);

istream& operator>> (istream& in, Polygonal& pol);

tuple<vector<point_t>, vector<point_t>> SplitLine(vector<point_t>& points, const point_t& point);