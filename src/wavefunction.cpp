#include <stdexcept>
#include <iostream>

#include "wavefunction.h"
#include "types.h"
#include "math.h"


// Constructor
Wavefunction::Wavefunction(CoefMatrix coefficient_matrix, Weights weights)
    : coefficient_matrix(coefficient_matrix), weights(weights) {}




Coefficient Wavefunction::get_coef(int x, int y){
    return coefficient_matrix[x][y];
}

int Wavefunction::get_height(){
    return coefficient_matrix.size();
}

int Wavefunction::get_width(){
    return coefficient_matrix[0].size();

}



// Method to get the collapsed tile at a given position
Tile Wavefunction::get_collapsed(int x, int y) {
    auto options = get_coef(x,y);

    if (options.size() != 1) {
        throw std::runtime_error("Error: The set of possible tiles at (" + std::to_string(x) + ", " + std::to_string(y) + ") does not contain exactly one tile.");
    }


    return *options.begin();  // Assuming the set contains at least one tile
}

// Method to get the entire collapsed matrix
World Wavefunction::get_all_collapsed() {

    std::cout << "in3";
    size_t height = coefficient_matrix.size();
    size_t width = coefficient_matrix[0].size();
    std::cout << "in";
    World collapsed(height, std::vector<Tile>(width));

    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            collapsed[x][y] = get_collapsed(x, y);
        }
    }
    return collapsed;
}

// Method to calculate the Shannon entropy for a given coordinate
float Wavefunction::shannon_entropy(int x, int y) {

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
bool Wavefunction::is_fully_collapsed() {
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
    float rnd = noise();

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
