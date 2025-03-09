#include <stdexcept>
#include <iostream>
#include <stack>
#include <algorithm>

#include "wavefunction.h"
#include "types.h"
#include "math.h"
#include "direction.h"


// Constructor
Wavefunction::Wavefunction(CoefMatrix coefficient_matrix, Weights weights)
    : coefficient_matrix(coefficient_matrix), weights(weights) {}




Coefficient Wavefunction::get_coef(int x, int y) const{
    return coefficient_matrix[x][y];
}

int Wavefunction::get_height() const{
    return coefficient_matrix.size();
}

int Wavefunction::get_width() const{
    return coefficient_matrix[0].size();

}



// Method to get the collapsed tile at a given position
Tile Wavefunction::get_collapsed(int x, int y) const{
    auto options = get_coef(x,y);

    if (options.size() != 1) {
        throw std::runtime_error("Error: The set of possible tiles at (" + std::to_string(x) + ", " + std::to_string(y) + ") does not contain exactly one tile.");
    }


    return *options.begin();  // Assuming the set contains at least one tile
}

// Method to get the entire collapsed matrix
World Wavefunction::get_all_collapsed() const{

    size_t height = coefficient_matrix.size();
    size_t width = coefficient_matrix[0].size();
    World collapsed(height, std::vector<Tile>(width));

    for (size_t x = 0; x < height; ++x) {
        for (size_t y = 0; y < width; ++y) {
            collapsed[x][y] = get_collapsed(x, y);
        }
    }
    return collapsed;
}

// Method to calculate the Shannon entropy for a given coordinate
float Wavefunction::shannon_entropy(int x, int y) const{

    float sum_of_weights = 0.0f;
    float sum_of_weight_log_weights = 0.0f;
    auto& options = coefficient_matrix[x][y];

    for (const auto& opt : options) {
        float weight = weights.at(opt);
        sum_of_weights += weight;
        sum_of_weight_log_weights += weight * std::log(weight);
    }

    return std::log(sum_of_weights) - (sum_of_weight_log_weights / sum_of_weights);
}

// Method to check if the wavefunction is fully collapsed
bool Wavefunction::is_fully_collapsed() const{
    for (const auto& row : coefficient_matrix) {
        for (const auto& sq : row) {
            if (sq.size() > 1) {
                return false;
            }
        }
    }
    return true;
}

// Method to collapse the wavefunction at a given coordinate
void Wavefunction::collapse(int x, int y) {

    auto& opts = coefficient_matrix[x][y];
    std::vector<std::pair<Tile, int>> filtered_tiles_with_weights;

    // Filter the options with weights
    for (const auto& tile : opts) {
        filtered_tiles_with_weights.emplace_back(tile, weights.at(tile));
    }

    // Calculate the total weight
    int total_weights = 0;
    for (const auto& [tile, weight] : filtered_tiles_with_weights) {
        total_weights += weight;
    }

    // Randomly choose a tile based on the weights
    float rnd = noise()*total_weights;

    Tile chosen = filtered_tiles_with_weights[0].first;
    for (const auto& [tile, weight] : filtered_tiles_with_weights) {
        rnd -= weight;
        if (rnd < 0) {
            chosen = tile;
            break;
        }
    }

    // Set the chosen tile as the only option for this coordinate
    opts.clear();
    opts.insert(chosen);
}

// Method to constrain the wavefunction by removing a forbidden tile at a given coordinate
void Wavefunction::constrain(int x, int y, Tile forbidden_tile) {
    coefficient_matrix[x][y].erase(forbidden_tile);
}


Coordinate Wavefunction::min_entropy_coords() const{

    auto wf = (*this);

    int h = wf.get_height();
    int w = wf.get_width();

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


void Wavefunction::propagate(int x, int y, BuildRules& build_rules) {
    std::stack<std::pair<int, int>> stack;

    stack.push({x, y});  // Push the initial coordinate (x, y) to the stack

    int wfh = get_height();  // Get the height using 'this' pointer
    int wfw = get_width();   // Get the width using 'this' pointer

    while (!stack.empty()) {
        auto cur_coords = stack.top();
        stack.pop();
        int cur_x = cur_coords.first;
        int cur_y = cur_coords.second;

        // Get the possible tiles at the current location using 'this' pointer
        auto cur_possible_tiles = get_coef(cur_x, cur_y);

        // Iterate through each valid direction from the current coordinate
        auto in_bound_directions = get_in_bound_directions(cur_x, cur_y, wfh, wfw);
        for (const Direction& dir : in_bound_directions) {
            int other_x = cur_x + dir.x;
            int other_y = cur_y + dir.y;

            // Get the possible tiles at the adjacent location using 'this' pointer
            Coefficient other_possible_tiles = get_coef(other_x, other_y);

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
                    constrain(other_x, other_y, other_tile);  // Use 'this' to call the method
                    stack.push({other_x, other_y});
                }
            }
        }
    }
}

