#ifndef WAVEFUNCTION_H
#define WAVEFUNCTION_H

#include <vector>
#include <set>
#include <map>
#include <cmath>
#include <random>
#include "types.h"  // Assuming the required types are defined here
#include "tile.h"
class Wavefunction {
public:
    // Constructor
    Wavefunction(CoefMatrix coefficient_matrix, Weights weights);

    // Getter
    Coefficient get_coef(int x, int y);

    // Get height
    int get_height();

    int get_width();


    // Method to get the collapsed tile at a given position
    Tile get_collapsed(int x, int y);

    // Method to get the entire collapsed matrix
    World get_all_collapsed();

    // Method to calculate the Shannon entropy for a given coordinate
    float shannon_entropy(int x, int y);

    // Method to check if the wavefunction is fully collapsed
    bool is_fully_collapsed();

    // Method to collapse the wavefunction at a given coordinate
    void collapse(int x, int y);

    // Method to constrain the wavefunction by removing a forbidden tile at a given coordinate
    void constrain(int x, int y, Tile forbidden_tile);

private:
    CoefMatrix coefficient_matrix;  // The coefficient matrix
    Weights weights;                       // The weight of each tile
};

#endif  // WAVEFUNCTION_H
