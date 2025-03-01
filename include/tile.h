#ifndef TILE_H
#define TILE_H

#include <stdexcept>
#include <string>
#include <ostream>  // for std::ostream

enum class Tile { L, C, S };

// Function prototypes
Tile charToTile(char c);
char tileToChar(Tile t);

// Comparison operators declaration
bool operator==(Tile lhs, Tile rhs);
bool operator!=(Tile lhs, Tile rhs);
bool operator<(Tile lhs, Tile rhs);
bool operator>(Tile lhs, Tile rhs);
bool operator<=(Tile lhs, Tile rhs);
bool operator>=(Tile lhs, Tile rhs);

std::string to_string(Tile tile);
std::ostream& operator<<(std::ostream& os, const Tile& t);

#endif
