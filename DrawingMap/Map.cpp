#include "Map.h"

using namespace std;

Map::Map(vector<vector<int>>& map2d) {
    this->map2d = map2d;
    this->rows= map2d.size();
    this->columns = map2d[0].size();
}

int Map::getRows() {
    return this->rows;
}

int Map::getColumns() {
    return this->columns;
}

vector<vector<int>> Map::getMap() {
    return this->map2d;
}

void Map::setMap(vector<vector<int>>& map2d) {
    this->map2d = map2d;
    this->rows = map2d.size();
    this->columns = map2d[0].size();
}

void Map::setValue(int x, int y, int value) {
    this->map2d[y][x] = value;
}

void Map::addWalls() {
    for (size_t j = 0; j < columns; ++j) {
        map2d[0][j] = 1;
        map2d[rows - 1][j] = 1;
    }
    for (size_t i = 0; i < rows; ++i) {
        map2d[i][0] = 1;
        map2d[i][columns - 1] = 1;
    }
}

void Map::addObstacle(const size_t x1, const size_t y1, const size_t x2, const size_t y2)
{
    for (size_t i = y1; i <= y2; ++i){
        for (size_t j = x1; j <= x2; ++j){
            map2d[i][j] = 1;
        }
    }
}

bool Map::checkIfAllCleaned() {
    for (const auto& j : map2d) {
        for (auto i : j) {
            if (i == 0) {
                return false;
            }
        }
    }
    return true;
}

bool Map::operator==(vector<vector<int>>& m2) {
    return this->map2d == m2;
}