#include "direction.h"

Direction::Direction(int x, int y)
    : x(x), y(y) {}


// Define the direction constants
Direction UP = Direction(-1, 0);
Direction DOWN = Direction(1, 0);
Direction LEFT = Direction(0, -1);
Direction RIGHT = Direction(0, 1);

// Declare VALID_DIRECTIONS as a vector of Direction objects
const std::vector<Direction> VALID_DIRECTIONS = {
    UP,    // UP
    DOWN,  // DOWN
    LEFT,  // LEFT
    RIGHT  // RIGHT
};


// Define the << operator for Direction
std::string Direction::as_str() const{
    // Check the direction using operator==

    std::string dir_str = "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    if (*this == UP) {
        return "UP" + dir_str;
    }
    if (*this == DOWN) {
        return "DOWN"+ dir_str;
    }
    if (*this == LEFT) {
        return "LEFT"+ dir_str;
    } 
    if (*this == RIGHT) {
        return "RIGHT"+ dir_str;
    }
    
    return "INVALID"+dir_str;
    
}

std::vector<Direction> get_in_bound_directions(int x, int y, int h, int w) {
    std::vector<Direction> result;
    for (const Direction& dir : VALID_DIRECTIONS) {
        int new_x = x + dir.x;
        int new_y = y + dir.y;
        bool in_bounds = (new_x >= 0 && new_x < h && new_y >= 0 && new_y < w);
        if (in_bounds) {
            result.push_back(dir);
        }
    }
    return result;
}