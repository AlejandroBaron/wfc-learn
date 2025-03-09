 
#include <stdexcept>

#include "direction.h"
#include "rule.h"

BuildRule::BuildRule(Tile tile1, Tile tile2,  Direction dir)
    : tile1(tile1), tile2(tile2), dir(dir) {}


BuildRule BuildRule::x_flip() const{
    Direction flipped_dir = Direction(-dir.x, dir.y); 
    return BuildRule(tile2, tile1, flipped_dir);
};

BuildRule BuildRule::y_flip() const {
    Direction flipped_dir = Direction(dir.x, -dir.y);
    return BuildRule(tile2, tile1, flipped_dir);
}
