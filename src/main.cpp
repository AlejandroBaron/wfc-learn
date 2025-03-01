#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>

#include "io.h"
#include "rule.h"


using Tile = char;


int main() {
    std::vector<std::vector<char>> matrix = {
        {'L','L','L','L'},
        {'L','L','L','L'},
        {'L','L','L','L'},
        {'L','C','C','L'},
        {'C','S','S','C'},
        {'S','S','S','S'},
        {'S','S','S','S'},
    };

    prettyPrintMatrix(matrix);

    // Create a vector to store the collection of compatibilities
    std::vector<BuildRule> compatibilities;
    std::unordered_map<char,int> weights;
    int matrix_height = matrix.size();
    int matrix_width = matrix[0].size();

    for (int i = 0; i < matrix_height; ++i) {
            for (int j = 0; j < matrix_width; ++j) {
                Tile tile = matrix[i][j];
                weights[tile] +=1;
            }
    }

    std:: cout << "Counts" << std::endl;
    for (const auto& pair : weights) {
        std::cout << pair.first << " => " << pair.second << std::endl;
    }

    // Add some compatibilities to the collection
    compatibilities.push_back(BuildRule(1, 2, "Rule1"));
    compatibilities.push_back(BuildRule(3, 4, "Rule2"));
    compatibilities.push_back(BuildRule(5, 6, "Rule3"));

    // Display the compatibilities
    for (const auto& Rule : compatibilities) {
        std::cout << "tile1: " << Rule.tile1 << ", tile2: " << Rule.tile2 << ", Rule: " << Rule.RULE << std::endl;
    }

    return 0;
}