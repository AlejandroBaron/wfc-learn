#ifndef TYPES_H
#define TYPES_H


#include <unordered_map>
#include <set>
#include "tile.h"
#include "rule.h"

using World = std::vector<std::vector<Tile>>;
using Coefficient = std::set<Tile>;
using CoefMatrix = std::vector<std::vector<Coefficient>>;
using Weights = std::unordered_map<Tile,int>;
using BuildRules = std::set<BuildRule>;
using Size = std::tuple<int,int>;
using RawInput = std::vector<std::vector<char>>;
struct Coordinate
{
    int x;
    int y;
};


#endif