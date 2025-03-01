// rule.h

#ifndef RULE_H
#define RULE_H

#include <string>

// Define a struct to represent the BuildRule
struct BuildRule {
    int tile1;         // Example type for tile1
    int tile2;         // Example type for tile2
    std::string RULE; // Example type for RULE

    // Constructor to initialize the BuildRule
    BuildRule(int tile1, int tile2, const std::string& rule);
};

#endif // RULE_H
