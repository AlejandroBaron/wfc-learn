// rule.cpp

#include "rule.h" // Include the header file
#include <stdexcept> // Include this for exception handling



BuildRule::BuildRule(Tile tile1, Tile tile2,  Direction dir)
    : tile1(tile1), tile2(tile2), dir(dir) {}

Direction::Direction(int x, int y)
    : x(x), y(y) {}


// Define the direction constants
Direction UP = Direction(-1, 0);
Direction DOWN = Direction(1, 0);
Direction LEFT = Direction(0, -1);
Direction RIGHT = Direction(0, 1);

// Declare valid_directions as a vector of Direction objects
std::vector<Direction> valid_directions = {
    UP,    // UP
    DOWN,  // DOWN
    LEFT,  // LEFT
    RIGHT  // RIGHT
};

// Define the << operator for Direction
std::ostream& operator<<(std::ostream& os, const Direction& dir) {
    // Check the direction using operator==
    if (dir == UP) {
        os << "UP (" << dir.x << ", " << dir.y << ")";
    } else if (dir == DOWN) {
        os << "DOWN (" << dir.x << ", " << dir.y << ")";
    } else if (dir == LEFT) {
        os << "LEFT (" << dir.x << ", " << dir.y << ")";
    } else if (dir == RIGHT) {
        os << "RIGHT (" << dir.x << ", " << dir.y << ")";
    } else {
        os << "UNKNOWN (" << dir.x << ", " << dir.y << ")";
    }
    return os;
}