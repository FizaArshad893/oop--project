#include "Stronghold.h"

Map::Map(int w, int h) : width(w), height(h), positionCount(0), positionCapacity(10) {
    grid = new int* [width];
    for (int i = 0; i < width; i++) {
        grid[i] = new int[height];
        for (int j = 0; j < height; j++) grid[i][j] = 0;
    }
    positions = new Position[positionCapacity];
    for (int i = 0; i < positionCapacity; i++) positions[i].isUsed = false;
}

Map::~Map() {
    for (int i = 0; i < width; i++) {
        delete[] grid[i];
    }
    delete[] grid;
    delete[] positions;
}

void Map::moveKingdom(const string& kingdom, int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height)
        throw CustomException("Invalid map coordinates");
    for (int i = 0; i < positionCount; i++) {
        if (positions[i].kingdom == kingdom && positions[i].isUsed) {
            positions[i].x = x;
            positions[i].y = y;
            return;
        }
    }
    if (positionCount >= positionCapacity)
        throw CustomException("Position capacity exceeded");
    positions[positionCount].kingdom = kingdom;
    positions[positionCount].x = x;
    positions[positionCount].y = y;
    positions[positionCount].isUsed = true;
    positionCount++;
}

int Map::getDistance(const string& kingdom1, const string& kingdom2) const {
    int x1 = -1, y1 = -1, x2 = -1, y2 = -1;
    for (int i = 0; i < positionCount; i++) {
        if (positions[i].isUsed) {
            if (positions[i].kingdom == kingdom1) {
                x1 = positions[i].x;
                y1 = positions[i].y;
            }
            if (positions[i].kingdom == kingdom2) {
                x2 = positions[i].x;
                y2 = positions[i].y;
            }
        }
    }
    if (x1 == -1 || x2 == -1)
        throw CustomException("Kingdom not found on map");
    return abs(x1 - x2) + abs(y1 - y2);
}
