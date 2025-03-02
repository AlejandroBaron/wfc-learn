#ifndef TYPES_H
#define TYPES_H


#include <unordered_map>
#include "tile.h"

using World = std::vector<std::vector<Tile>>;


using Coefficient = std::set<Tile>;
using CoefMatrix = std::vector<std::vector<Coefficient>>;
using Weights = std::unordered_map<Tile,int>;



#endif