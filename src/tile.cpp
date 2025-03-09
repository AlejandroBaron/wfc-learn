#include "tile.h"

Tile charToTile(char c) {
    switch (c) {
        case 'L': return Tile::L;
        case 'C': return Tile::C;
        case 'S': return Tile::S;
        default: throw std::invalid_argument("Invalid character for Tile");
    }
}

char tileToChar(Tile t) {
    switch (t) {
        case Tile::L: return 'L';
        case Tile::C: return 'C';
        case Tile::S: return 'S';
        default: throw std::invalid_argument("Invalid Tile value");
    }
}

bool operator==(Tile lhs, Tile rhs) {
    return static_cast<int>(lhs) == static_cast<int>(rhs);
}

bool operator!=(Tile lhs, Tile rhs) {
    return !(lhs == rhs);
}

bool operator<(Tile lhs, Tile rhs) {
    return static_cast<int>(lhs) < static_cast<int>(rhs);
}

bool operator>(Tile lhs, Tile rhs) {
    return static_cast<int>(lhs) > static_cast<int>(rhs);
}

bool operator<=(Tile lhs, Tile rhs) {
    return !(lhs > rhs);
}

bool operator>=(Tile lhs, Tile rhs) {
    return !(lhs < rhs);
}

std::string tile2Char(Tile tile) {
    switch (tile) {
        case Tile::L: return "L";
        case Tile::C: return "C";
        case Tile::S: return "S";
        default: return "Unknown";
    }
}

std::ostream& operator<<(std::ostream& os, const Tile& t) {
    return os <<  tile2Char(t);
}