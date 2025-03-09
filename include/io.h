#ifndef PRETTY_PRINT_MATRIX_H
#define PRETTY_PRINT_MATRIX_H

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "types.h"



void pprint_input(const RawInput& matrix);
World world2input(const RawInput& charMatrix);
RawInput input2world(const World& world);
RawInput read_input(const std::string &filename);


#endif
