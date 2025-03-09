#ifndef PRETTY_PRINT_MATRIX_H
#define PRETTY_PRINT_MATRIX_H

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "types.h"



void pprint_input(const RawInput& matrix);
World input2world(const RawInput& charMatrix);
RawInput world2input(const World& world);
RawInput read_input(const std::string &filename);
void pprint_coefmatrix(const CoefMatrix& coefMatrix);

#endif
