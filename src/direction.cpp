#include "direction.h"

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