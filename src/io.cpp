#include "io.h"
#include <iostream>
#include <unordered_map>

// ANSI color codes
const std::unordered_map<char, std::string> PALETTE = {
    {'L', "\033[32m"}, // Green
    {'S', "\033[34m"}, // Blue
    {'C', "\033[33m"}, // Yellow
};

void prettyPrintMatrix(const std::vector<std::vector<char>>& matrix) {
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
