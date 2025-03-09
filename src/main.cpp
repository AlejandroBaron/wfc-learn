#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

#include "io.h"
#include "rule.h"
#include "tile.h"
#include "wavefunction.h"
#include "types.h"
#include "math.h"


Tile L = Tile::L;
Tile C = Tile::C;
Tile S = Tile::S;


// Init the matrix to all possible states
CoefMatrix init_coef_matrix(int x, int y) {

    Coefficient all = {L,C,S};
    CoefMatrix matrix(x, std::vector<Coefficient> (y, all));
    return matrix;
}

int main(int argc, char *argv[]){
    std::string world_file = argv[1];
    std::string mode = (argc > 2) ? argv[2] : "WEIGHTED";

    RawInput input = read_input(world_file);
    
    int gen_size = 16;
    pprint_input(input);
    
    World world = input2world(input);

    // Create a vector to store the collection of build_rules

    Weights weights;
    int world_h = world.size();
    int world_w = world[0].size();

    BuildRules build_rules;
    for (int i = 0; i < world_h; ++i) {
            for (int j = 0; j < world_w; ++j) {
                Tile tile = world[i][j];
                weights[tile] = (mode=="CONSTANT") ? 1 : weights[tile] + 1;
                auto in_bound_directions = get_in_bound_directions(i, j, world_h, world_w);
                for (const Direction& dir : in_bound_directions){
                        int i2 = i + dir.x;
                        int j2 = j + dir.y;
                        Tile neighbour = world[i2][j2];
                        BuildRule rule(tile, neighbour, dir);
                        build_rules.insert(rule);
                        build_rules.insert(rule.x_flip());
                        build_rules.insert(rule.y_flip());
                    
                }
            }
    }

    std::cout << "Counts" << std::endl;
    for (const auto& pair : weights) {
        std::cout << pair.first << " => " << pair.second << std::endl;
    }

    std::cout << "Rules" << std::endl;
    for (const auto& rule: build_rules){
        std::cout << rule.tile1 << " " << rule.tile2 << " " << rule.dir.as_str() << std::endl;
    }

    CoefMatrix coef_matrix = init_coef_matrix(gen_size, gen_size);
    Wavefunction wf(coef_matrix,weights);

    int niter = 0;
    while (!wf.is_fully_collapsed()){
   
        // Find min entropy coords
        Coordinate min_entropy = wf.min_entropy_coords();
        // Collapse
        wf.collapse(min_entropy.x, min_entropy.y);
        // propagate
        wf.propagate(min_entropy.x, min_entropy.y, build_rules);
        ++niter;
    }
    std::cout << "# Iter: " << niter << std::endl;

    World generation = wf.get_all_collapsed();

    RawInput parsed_gen = world2input(generation);
    pprint_input(parsed_gen);
    return 0;
}