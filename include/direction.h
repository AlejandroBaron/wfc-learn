#ifndef DIRECTION_H
#define DIRECTION_H

#include <string>
#include <vector>

struct Direction {
    int x;
    int y;
    Direction(int x, int y);


    bool operator==(const Direction& other) const {
        return x == other.x && y == other.y;
    }

    std::string as_str() const;
    
};

extern std::vector<Direction> valid_directions;

#endif