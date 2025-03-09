#ifndef DIRECTION_H
#define DIRECTION_H

#include <string>
#include <vector>

/**
 * @brief Represents a 2D direction vector
 * 
 * The Direction struct represents a two-dimensional direction vector
 * with x and y components. It's typically used for grid-based movement
 * or position calculations.
 */
struct Direction {
    /// X-coordinate of the direction vector
    int x;
    /// Y-coordinate of the direction vector
    
    int y;
    /**
     * @brief Constructs a new Direction object
     * @param x The x-coordinate
     * @param y The y-coordinate
     */
    Direction(int x, int y);


    bool operator==(const Direction& other) const {
        return x == other.x && y == other.y;
    }

    /**
     * @brief Converts the direction to a string representation
     * @return std::string String representation of the direction
     */
    std::string as_str() const;
};

// Global vector containing all valid directions for the application
extern const std::vector<Direction> VALID_DIRECTIONS;

// Function to get the in-bound directions for a given coordinate
std::vector<Direction> get_in_bound_directions(int x, int y, int h, int w);
#endif