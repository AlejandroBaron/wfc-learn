// rule.h

#ifndef RULE_H
#define RULE_H

#include <string>
#include <vector>

#include "tile.h"

struct Direction {
    int x;
    int y;
    Direction(int x, int y);


    bool operator==(const Direction& other) const {
        return x == other.x && y == other.y;
    }
    
};
struct BuildRule {
    Tile tile1;
    Tile tile2;
    Direction dir; 

    // Constructor to initialize the BuildRule
    BuildRule(Tile tile1, Tile tile2, const Direction rule);

    // Implementing comparison makes suitable for sets
    bool operator< (const BuildRule& other) const {
        if (tile1 != other.tile1) return tile1 < other.tile1;
        if (tile2 != other.tile2) return tile2 < other.tile2;
        return dir.x < other.dir.x || (dir.x == other.dir.x && dir.y < other.dir.y);
    }
};


extern std::vector<Direction> valid_directions;
std::ostream& operator<<(std::ostream& os, const Direction& dir);

#endif // RULE_H
