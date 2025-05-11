#ifndef MAP_HPP
#define MAP_HPP

#include <string>

class Map {
private:
    static const int SIZE = 5;
    static const int MAX_KINGDOMS = 10;
    struct Position {
        std::string name;
        int x;
        int y;
        bool active;
    };
    Position kingdomPositions[MAX_KINGDOMS];
    int positionCount;
public:
    Map();
    bool placeKingdom(const std::string& name, int x, int y);
    bool moveKingdom(const std::string& name, int newX, int newY);
    int getDistance(const std::string& k1, const std::string& k2) const;
    void display() const;
};

#endif 