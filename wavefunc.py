import random
import math
from typing import Literal

# Types
Tile = str
Coordinates = tuple[int, int]
Up = tuple[Literal[1], Literal[0]]; Down = tuple[Literal[-1], Literal[0]]
Left = tuple[Literal[0], Literal[-1]]; Right = tuple[Literal[0], Literal[1]]
Direction = Up | Down | Left | Right
Compatibility = tuple[Tile, Tile, Direction]
Weights = dict[Tile, int]
Coefficients = set[Tile]
CoefMatrix = list[list[Coefficients]]

class Wavefunction(object):

    """The Wavefunction class is responsible for storing which tiles
    are permitted and forbidden in each location of an output image.
    """


    def __init__(self, coefficient_matrix: CoefMatrix, weights: Weights):
        self.coefficient_matrix = coefficient_matrix
        self.weights = weights


    def get_collapsed(self, x,y) -> Tile:
        options = self.coefficient_matrix[y][x]
        return options[0]

    def get_all_collapsed(self) -> list[list[Tile]]:
        height = len(self.coefficient_matrix)
        width = len(self.coefficient_matrix[0])

        collapsed: list[list[Tile]] = []
        for y in range(height):
            row: list[Tile] = []
            for x in range(width):
                row.append(self.get_collapsed((y, x)))
            collapsed.append(row)

        return collapsed

    def shannon_entropy(self, co_ords: Coordinates) -> float:
        y, x = co_ords

        sum_of_weights = 0
        sum_of_weight_log_weights = 0
        for opt in self.coefficient_matrix[y][x]:
            weight = self.weights[opt]
            sum_of_weights += weight
            sum_of_weight_log_weights += weight * math.log(weight)

        return math.log(sum_of_weights) - (sum_of_weight_log_weights / sum_of_weights)


    def is_fully_collapsed(self) -> bool:
        for row in self.coefficient_matrix:
            for sq in row:
                if len(sq) > 1:
                    return False

        return True

    def collapse(self, co_ords: Coordinates) -> None:
        y, x = co_ords
        opts = self.coefficient_matrix[y][x]
        filtered_tiles_with_weights = [(tile, weight) for tile, weight in self.weights.items() if tile in opts]

        total_weights = sum([weight for _, weight in filtered_tiles_with_weights])
        rnd = random.random() * total_weights

        chosen = filtered_tiles_with_weights[0][0]
        for tile, weight in filtered_tiles_with_weights:
            rnd -= weight
            if rnd < 0:
                chosen = tile
                break

        self.coefficient_matrix[y][x] = set([chosen])

    def constrain(self, co_ords: Coordinates, forbidden_tile: Tile) -> None:
        y, x = co_ords
        self.coefficient_matrix[y][x].remove(forbidden_tile)


