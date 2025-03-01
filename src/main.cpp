#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>

#include "io.h"
#include "rule.h"
#include "tile.h"

using World = std::vector<std::vector<Tile>>;
Tile L = Tile::L;
Tile C = Tile::C;
Tile S = Tile::S;

using Coefficient = std::set<Tile>;
using CoefMatrix = std::vector<std::vector<Coefficient>>;

World convertToTileMatrix(const std::vector<std::vector<char>>& charMatrix) {
    int rows = charMatrix.size();
    int cols = charMatrix[0].size();
    
    std::vector<std::vector<Tile>> tileMatrix(rows, std::vector<Tile>(cols));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            tileMatrix[i][j] = charToTile(charMatrix[i][j]); // Convert char to Tile enum
        }
    }

    return tileMatrix;
}

CoefMatrix getCoefMatrix(int x, int y) {

    Coefficient all = {L,C,S};
    CoefMatrix matrix(x, std::vector<Coefficient> (y, all));
    return matrix;
}



int main() {
    std::vector<std::vector<char>> input = {
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

    std::unordered_map<Tile,int> weights;
    int matrix_height = matrix.size();
    int matrix_width = matrix[0].size();

    std::set<BuildRule> build_rules;
    for (int i = 0; i < matrix_height; ++i) {
            for (int j = 0; j < matrix_width; ++j) {
                Tile tile = matrix[i][j];
                weights[tile] +=1;

                for (const Direction& dir : valid_directions){
                        int i2 = i - dir.x;
                        int j2 = j - dir.y;
                        bool valid_dir = (i2 >= 0 && i2 < matrix_height && j2 >= 0 && j2 < matrix_width); // Check for Out of bounds
                        if (valid_dir){
                            Tile neighbour = matrix[i2][j2];
                            build_rules.insert(BuildRule(tile, neighbour, dir));
                        }
                }
            }
    }

    std:: cout << "Counts" << std::endl;
    for (const auto& pair : weights) {
        std::cout << pair.first << " => " << pair.second << std::endl;
    }

    CoefMatrix x = getCoefMatrix(matrix_height,matrix_width);
    
    for (int i = 0; i < matrix_height; ++i) {
        for (int j = 0; j < matrix_width; ++j) {
            Coefficient coef = x[i][j];
            for (const auto& elem : coef) {
                std::cout << elem << std::endl;
            }
        }
    }
    

    return 0;
}