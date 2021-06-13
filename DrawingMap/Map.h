#pragma once
#include<vector>
#include<iostream>
#include <tuple>
using namespace std;
class Map
{
private:
    int rows;
    int columns;
    vector<vector<int>> map2d;
public:
    Map();
    Map(vector<vector<int>>& map2d);
    int getRows();
    int getColumns();
    vector<vector<int>> getMap();
    void setMap(vector<vector<int>>& map2d);
    void setValue(int x, int y, int value);
    void addWalls();
    void addObstacle(const size_t x1, const size_t y1, const size_t x2, const size_t y2);
    bool checkIfAllCleaned();
    bool operator==(vector<vector<int>>& m2);
};