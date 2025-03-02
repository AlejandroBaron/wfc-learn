#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <random>
#include <limits>
#include <stack>
#include <tuple>
#include <algorithm>


#include "io.h"
#include "rule.h"
#include "tile.h"
#include "wavefunction.h"
#include "types.h"
#include "math.h"


Tile L = Tile::L;
Tile C = Tile::C;
Tile S = Tile::S;

struct Coordinate
{
    int x;
    int y;
};

using BuildRules = std::set<BuildRule>;
using Size = std::tuple<int,int>;
using RawInput = std::vector<std::vector<char>>;

std::vector<Direction> get_in_bound_directions(int x, int y, int h, int w) {
    std::vector<Direction> result;
    for (const Direction& dir : valid_directions) {
        int new_x = x + dir.x;
        int new_y = y + dir.y;
        bool in_bounds = (new_x >= 0 && new_x < h && new_y >= 0 && new_y < w);
        if (in_bounds) {
            result.push_back(dir);
        }
    }
    return result;
}

World convertToTileMatrix(const RawInput& charMatrix) {
    int rows = charMatrix.size();
    int cols = charMatrix[0].size();
    
    World tileMatrix(rows, std::vector<Tile>(cols));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            tileMatrix[i][j] = charToTile(charMatrix[i][j]); // Convert char to Tile enum
        }
    }

    return tileMatrix;
}

RawInput convertToCharMatrix(const std::vector<std::vector<Tile>>& tileMatrix) {
    int rows = tileMatrix.size();
    std:: cout << rows ;
    int cols = tileMatrix[0].size();
    
    std:: cout << rows ;
    RawInput charMatrix(rows, std::vector<char>(cols));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            charMatrix[i][j] = tileToChar(tileMatrix[i][j]); // Convert Tile enum back to char
        }
    }

    return charMatrix;
}


CoefMatrix getCoefMatrix(int x, int y) {

    Coefficient all = {L,C,S};
    CoefMatrix matrix(x, std::vector<Coefficient> (y, all));
    return matrix;
}


Coordinate min_entropy_coords(Wavefunction& wf){

    int h = wf.get_height();
    int w = wf.get_width();

    std::set<BuildRule> build_rules;
    float min_entropy = std::numeric_limits<float>::infinity();
    int min_i = 0, min_j = 0;
    for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                int n_states = wf.get_coef(i,j).size();
                if (n_states == 1){
                    continue;
                }

                float entropy = wf.shannon_entropy(i,j);
                entropy += noise() / 1000;
                
                if (entropy < min_entropy){
                    min_entropy = entropy;
                    min_i = i;
                    min_j = j;
                }


        }
    }

    Coordinate cord = {min_i, min_j};
    return cord;
}



void propagate(int x, int y, Wavefunction& wf, BuildRules& build_rules, const Size& output_size) {
    std::stack<std::pair<int, int>> stack;

    stack.push({x, y});  // Push the initial coordinate (x, y) to the stack

    int wfh = wf.get_height();
    int wfw = wf.get_width();

    while (!stack.empty()) {
        auto cur_coords = stack.top();
        stack.pop();
        int cur_x = cur_coords.first;
        int cur_y = cur_coords.second;

        // Get the possible tiles at the current location
        auto cur_possible_tiles = wf.get_coef(cur_x, cur_y);

        // Iterate through each valid direction from the current coordinate
        auto in_bound_directions = get_in_bound_directions(cur_x, cur_y, wfh, wfw);
        for (const Direction& dir : in_bound_directions) {
            int other_x = cur_x + dir.x;
            int other_y = cur_y + dir.y;

            // Get the possible tiles at the adjacent location
            Coefficient other_possible_tiles = wf.get_coef(other_x, other_y);
            // Iterate through each tile in the adjacent location's wavefunction
            for (const auto& other_tile : other_possible_tiles) {
                // Check compatibility with any tile from the current location
                bool other_tile_is_possible = std::any_of(cur_possible_tiles.begin(), cur_possible_tiles.end(),
                    [&](const Tile& cur_tile) {
                        BuildRule intention(cur_tile, other_tile, dir);
                        return build_rules.find(intention) != build_rules.end();
                    });

                // If no compatibility, constrain the adjacent tile
                if (!other_tile_is_possible) {
                    wf.constrain(other_x, other_y, other_tile);
                    stack.push({other_x, other_y});
                }
                else {
                }
            }
        }
    }
}



int main() {
    RawInput input = {
        {'L','L','L','L'},
        {'L','L','L','L'},
        {'L','L','L','L'},
        {'L','C','C','L'},
        {'C','S','S','C'},
        {'S','S','S','S'},
        {'S','S','S','S'},
    };
    prettyPrintMatrix(input);
    World matrix = convertToTileMatrix(input);

    // Create a vector to store the collection of build_rules

    Weights weights;
    int matrix_height = matrix.size();
    int matrix_width = matrix[0].size();

    BuildRules build_rules;
    for (int i = 0; i < matrix_height; ++i) {
            for (int j = 0; j < matrix_width; ++j) {
                Tile tile = matrix[i][j];
                weights[tile] +=1;
                auto in_bound_directions = get_in_bound_directions(i, j, matrix_height, matrix_width);
                for (const Direction& dir : in_bound_directions){
                        int i2 = i + dir.x;
                        int j2 = j + dir.y;
                        Tile neighbour = matrix[i2][j2];
                        build_rules.insert(BuildRule(tile, neighbour, dir));
                    
                }
            }
    }

    std:: cout << "Counts" << std::endl;
    for (const auto& pair : weights) {
        std::cout << pair.first << " => " << pair.second << std::endl;
    }

    CoefMatrix coef_matrix = getCoefMatrix(matrix_height, matrix_width);

    Wavefunction wf(coef_matrix,weights);

    // Find min entropy coords

    int niter = 0;
    while (!wf.is_fully_collapsed()){

        Coordinate min_entropy = min_entropy_coords(wf);
        // Collapse
        wf.collapse(min_entropy.x, min_entropy.y);
        // propagate
        propagate(min_entropy.x, min_entropy.y, wf, build_rules, {16,16});
        ++niter;
    }
    std::cout <<"# Iter: " << niter << std::endl;

    World generation = wf.get_all_collapsed();
    // std:: cout << "in";
    // RawInput parsed_gen = convertToCharMatrix(generation);
    // std:: cout << "in";
    // prettyPrintMatrix(parsed_gen);

    

    return 0;
}