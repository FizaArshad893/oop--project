#include "Map.hpp"
#include <cmath>
#include <iostream>

Map::Map() : positionCount(0) {
    for (int i = 0; i < MAX_KINGDOMS; ++i) {
        kingdomPositions[i].active = false;
    }
}

bool Map::placeKingdom(const std::string& name, int x, int y) {
    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
        std::cout << "Invalid coordinates for " << name << std::endl;
        return false;
    }
    for (int i = 0; i < positionCount; ++i) {
        if (kingdomPositions[i].active && kingdomPositions[i].name == name) {
            kingdomPositions[i].x = x;
            kingdomPositions[i].y = y;
            std::cout << name << " placed at (" << x << ", " << y << ")" << std::endl;
            return true;
        }
    }
    if (positionCount >= MAX_KINGDOMS) {
        std::cout << "Cannot place kingdom: Maximum limit reached!" << std::endl;
        return false;
    }
    kingdomPositions[positionCount] = { name, x, y, true };
    positionCount++;
    std::cout << name << " placed at (" << x << ", " << y << ")" << std::endl;
    return true;
}

bool Map::moveKingdom(const std::string& name, int newX, int newY) {
    if (newX < 0 || newX >= SIZE || newY < 0 || newY >= SIZE) {
        std::cout << "Invalid move for " << name << std::endl;
        return false;
    }
    for (int i = 0; i < positionCount; ++i) {
        if (kingdomPositions[i].active && kingdomPositions[i].name == name) {
            kingdomPositions[i].x = newX;
            kingdomPositions[i].y = newY;
            std::cout << name << " moved to (" << newX << ", " << newY << ")" << std::endl;
            return true;
        }
    }
    std::cout << "Kingdom " << name << " not found!" << std::endl;
    return false;
}

int Map::getDistance(const std::string& k1, const std::string& k2) const {
    int x1 = -1, y1 = -1, x2 = -1, y2 = -1;
    for (int i = 0; i < positionCount; ++i) {
        if (kingdomPositions[i].active) {
            if (kingdomPositions[i].name == k1) {
                x1 = kingdomPositions[i].x;
                y1 = kingdomPositions[i].y;
            }
            else if (kingdomPositions[i].name == k2) {
                x2 = kingdomPositions[i].x;
                y2 = kingdomPositions[i].y;
            }
        }
    }
    if (x1 == -1 || x2 == -1) {
        return -1;
    }
    int dx = x1 - x2;
    int dy = y1 - y2;
    return static_cast<int>(std::sqrt(dx * dx + dy * dy));
}

void Map::display() const {
    std::cout << "Map (5x5 Grid):" << std::endl;
    char grid[SIZE][SIZE] = { {' '} };
    for (int i = 0; i < positionCount; ++i) {
        if (kingdomPositions[i].active) {
            int x = kingdomPositions[i].x;
            int y = kingdomPositions[i].y;
            grid[x][y] = kingdomPositions[i].name[0];
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            std::cout << "[" << grid[i][j] << "]";
        }
        std::cout << std::endl;
    }
}