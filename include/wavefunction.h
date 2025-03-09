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
    /**
     * @brief Constructs a Wavefunction using a coefficient matrix and associated weights.
     *
     * @param coefficient_matrix The initial coefficient matrix.
     * @param weights The weights for each tile type.
     */
    Wavefunction(CoefMatrix coefficient_matrix, Weights weights);

    /**
     * @brief Retrieves the coefficient at the specified row and column.
     *
     * @param x The x-coordinate.
     * @param y The y-coordinate.
     * @return The coefficient located at (x, y).
     */
    Coefficient get_coef(int x, int y) const;

    /**
     * @brief Returns the wavefunction's height.
     *
     * @return The number of rows in the coefficient matrix.
     */
    int get_height() const;

    /**
     * @brief Returns the wavefunction's width.
     *
     * @return The number of columns in the coefficient matrix.
     */
    int get_width() const;

    /**
     * @brief Retrieves the collapsed tile at the specified location.
     *
     * @param x The x-coordinate.
     * @param y The y-coordinate.
     * @return The tile that the wavefunction collapses to at (x, y).
     */
    Tile get_collapsed(int x, int y) const;

    /**
     * @brief Returns the entire collapsed matrix.
     *
     * @return A matrix of tiles representing the collapsed state.
     */
    World get_all_collapsed() const;

    /**
     * @brief Calculates the Shannon entropy at the specified location.
     *
     * @param x The x-coordinate.
     * @param y The y-coordinate.
     * @return The Shannon entropy value at (x, y).
     */
    float shannon_entropy(int x, int y) const;

    /**
     * @brief Checks if the wavefunction is fully collapsed.
     *
     * @return True if all positions have a single possible tile, false otherwise.
     */
    bool is_fully_collapsed() const;

    /**
     * @brief Collapses the wavefunction at the specified location.
     *
     * @param x The x-coordinate.
     * @param y The y-coordinate.
     */
    void collapse(int x, int y);

    /**
     * @brief Constrains the wavefunction at (x, y) by removing a forbidden tile.
     *
     * @param x The x-coordinate.
     * @param y The y-coordinate.
     * @param forbidden_tile The tile to exclude at (x, y).
     */
    void constrain(int x, int y, Tile forbidden_tile);


    /**
     * @brief Returns the coordinate with min entropy value.
     *
     */
    Coordinate min_entropy_coords() const;

    void propagate(int x, int y, BuildRules& build_rules);

private:
    CoefMatrix coefficient_matrix;
    Weights weights;
};

#endif  // WAVEFUNCTION_H
