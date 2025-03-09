#include <iostream>
#include <unordered_map>

#include "io.h"
#include "tile.h"
#include "types.h"

// ANSI color codes
const std::unordered_map<char, std::string> PALETTE = {
    {'L', "\033[32m"}, // Green
    {'S', "\033[34m"}, // Blue
    {'C', "\033[33m"}, // Yellow
};

void pprint_input(const RawInput& matrix) {
    for (const auto& row : matrix) {
        for (char ch : row) {
            if (PALETTE.count(ch)) {
                std::cout << PALETTE.at(ch) << ch << " \033[0m"; // Reset color after character
            } else {
                std::cout << ch << " ";
            }
        }
        std::cout << "\n";
    }
}


World world2input(const RawInput& raw_input){
    int rows = raw_input.size();
    int cols = raw_input[0].size();
    
    World tileMatrix(rows, std::vector<Tile>(cols));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            tileMatrix[i][j] = charToTile(raw_input[i][j]); // Convert char to Tile enum
        }
    }

    return tileMatrix;
}


RawInput input2world(const World& world) {
    int rows = world.size();
    int cols = world[0].size();
    
    RawInput raw_input(rows, std::vector<char>(cols));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            raw_input[i][j] = tile2char(world[i][j]);
        }
    }

    return raw_input;
}


RawInput read_input(const std::string &filename){
    RawInput input;
    std::ifstream file(filename);

    if (!file) {
        std::cerr << "Error opening file!" << std::endl;
        exit(1);
    }

    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::vector<char> row;
        char cell;
        while (ss >> cell) {
            row.push_back(cell);
        }
        input.push_back(row); 
    }

    file.close();
    return input;
}

void pprint_coefmatrix(const CoefMatrix& coefMatrix) {
    for (const auto& row : coefMatrix) {
        for (const auto& coef : row) {
            
            bool not_collapsed = coef.size() != 1;
            if (not_collapsed) std::cout << "["; // Opening bracket
            
            for (const auto& tile : coef) {
                char tilechar = tile2char(tile);    
                std::cout << PALETTE.at(tilechar) << tile << " \033[0m";
            }
            if (not_collapsed) std::cout << "]"; // Closing bracket and tab
        }

        std::cout << "\n"; // Newline after each row
    }
    std::cout << std::endl; // Extra newline at the end
}