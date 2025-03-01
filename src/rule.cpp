// rule.cpp

#include "rule.h" // Include the header file

// Define the constructor for BuildRule
BuildRule::BuildRule(int tile1, int tile2, const std::string& rule)
    : tile1(tile1), tile2(tile2), RULE(rule) {}
