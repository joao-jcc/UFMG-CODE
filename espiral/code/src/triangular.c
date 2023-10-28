/*
Implementation of an algorithm that, given the index I of a point in a triangular spiral, 
returns the Cartesian coordinates (x, y) of the point.

Belo Horizonte, October 26, 2023
@author: joaocosta
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Define a struct to store coordinates of a vector
typedef struct Vector2 {
    int x;
    int y;
} Vector2;

// Trivial coordinates for indexes 0 and 1
Vector2 coordinate_zero = {0, 0};
Vector2 coordinate_one = {1, 0};

// Square Directions
Vector2 square_even_direction = {-2, -1};
Vector2 square_odd_direction = {2, -1};
// Horizontal directions
Vector2 right_direction = {1, 0};
Vector2 left_direction = {-1, 0};
// Diagonal directions
Vector2 direction_45 = {1, 1};
Vector2 direction_135 = {-1, 1};

// Linearly combines vectors
Vector2 linear_combination(int factor1, Vector2 c1, int factor2, Vector2 c2) {
    Vector2 result = {factor1 * c1.x + factor2 * c2.x, factor1 * c1.y + factor2 * c2.y};
    return result;
}

// Function to print the result: index and mapped coordinates
void print_result(int index, Vector2 coordinates) {
    printf("%u : (%d, %d)\n", index, coordinates.x, coordinates.y);
}

// Returns the nearest perfect square index to an index I
int nearest_root(int index) {
    int root = (int)round(sqrt(index)); // Approximate square root calculation
    return root; 
}

// Returns the coordinate of the perfect square using equation (1) or equation (2)
Vector2 square_coordinates(int root) {
    // Identifies the group of the perfect square: odd (1) or even (0)
    int group = root % 2 == 1;

    // Relative position of the perfect square in its respective group: Quadrant I (QI) or Quadrant P (QP)
    int relative_position = group ? (root - 1) / 2 : root / 2;

    // Final coordinate
    Vector2 result;

    // Coordinate for the odd group
    if (group) {
        result = linear_combination(1, coordinate_one, relative_position, square_odd_direction);
    } else {
        result = linear_combination(1, coordinate_zero, relative_position, square_even_direction);
    }

    return result;
}

int main(int argc, char* argv[]) {
    // Check the number of arguments in the command line
    if (argc != 2) {
        printf("Usage: [executable] [point-index]\n");
        exit(1);
    }

    // Convert the point index from char* to int
    int index = (int)strtol(argv[1], NULL, 10);

    // Check if the index is trivial: 0 or 1
    if (index == 0) {
        print_result(index, coordinate_zero);
        return 0;
    }

    if (index == 1) {
        print_result(index, coordinate_one);
        return 0;
    }

    // Nearest square index
    int root = nearest_root(index);
    int square_index = root * root;

    // Group of the perfect square: odd or even
    int group = square_index % 2 == 1;

    // Square coordinates
    Vector2 _square_coordinates = square_coordinates(root);

    // Relative position of the point with respect to the square index
    int relative_position = index - square_index;

    // Target Coordinates
    Vector2 target = _square_coordinates;

    if (relative_position > 0) {
        target = linear_combination(1, _square_coordinates, relative_position, group ? direction_135 : right_direction);
    } else if (relative_position < 0) {
        target = linear_combination(1, _square_coordinates, abs(relative_position), group ? left_direction : direction_45);
    }

    print_result(index, target);

    return 0;
}
