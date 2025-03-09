#ifndef TILE_H
#define TILE_H

#include <stdexcept>
#include <string>
#include <ostream>  // for std::ostream

enum class Tile { L, C, S };

// Function prototypes
/**
 * @brief Converts a character representation to a corresponding Tile object
 * @param c The character to be converted into a Tile
 * @return Tile The tile object corresponding to the input character
 * @throws std::invalid_argument if the character does not correspond to a valid tile
 */
Tile charToTile(char c);

/**
 * @brief Converts a Tile enumeration value to its corresponding character representation
 * 
 * @param t The tile enumeration value to convert
 * @return char The character representation of the tile
 */
char tile2char(Tile t);

// Comparison operators declaration
bool operator==(Tile lhs, Tile rhs);
bool operator!=(Tile lhs, Tile rhs);
bool operator<(Tile lhs, Tile rhs);
bool operator>(Tile lhs, Tile rhs);
bool operator<=(Tile lhs, Tile rhs);
bool operator>=(Tile lhs, Tile rhs);

std::ostream& operator<<(std::ostream& os, const Tile& t);

#endif
