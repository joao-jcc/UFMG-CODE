 /*
Implementation of an algorithm that, given the index I of a point in a square spiral, 
returns the Cartesian coordinates (x, y) of the point.

We apply an algorithm based on the perfect squares of the spiral.

Belo Horizonte, September 7, 2023
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
Vector2 coordinate_one = {0, 1};

// 45-degree direction
Vector2 identity_direction = {1, 1};
// Horizontal direction
Vector2 horizontal_direction = {1, 0};
// Vectical direction
Vector2 vertical_direction = {0, 1};


// Linearly combines vectors
Vector2 linear_combination(int factor1, Vector2 c1, int factor2, Vector2 c2) {
    Vector2 result = {factor1 * c1.x + factor2 * c2.x, factor1 * c1.y + factor2 * c2.y};

    return result;
}


// Function to print the result: index and mapped coordinates
void print_result(unsigned index, Vector2 coordinates) {
    printf("%u : (%d, %d)\n", index, coordinates.x, coordinates.y);
}


// Returns the nearest perfect square index to an index I
unsigned nearest_square(unsigned index) {
    unsigned root = round(sqrt(index)); // What is the asymptotic cost of a square root??
    return root * root; 
}



// Returns the coordinate of the perfect square using eq(1) or eq(2)
Vector2 square_coordinates(unsigned index_square) {
    unsigned root = sqrt(index_square);

    // Identifies the group of the perfect square: odd (1) or even (0)
    unsigned group = root % 2 == 1;

    // Relative position of the perfect square in its respective group: QI or QP
    unsigned relative_position = group ? (root - 1) / 2 : root / 2;

    // Final coordinate
    Vector2 result;

    // Coordinate for the odd group
    if (group) {
        result = linear_combination(1, coordinate_one, relative_position, identity_direction);
    } else {
        result = linear_combination(1, coordinate_zero, -1 * relative_position, identity_direction);
    }

    return result;
}


int main(int argc, char* argv[]) {
    // Check the number of arguments in the command line
    if (argc != 2) {
        printf("Usage: [executable] [point-index]\n");
        exit(1);
    }

    // Convert the point index from char* to unsigned
    unsigned index = atoi(argv[1]);

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
    unsigned square_index = nearest_square(index);

    // Relative position of the point in respect to the square index
    int relative_position = index - square_index;

    // Square coordiantes
    Vector2 _square_coordinates = square_coordinates(square_index);

    // Target Coordinates
    Vector2 target;

    // Group of the perfect sqaure: odd or even
    unsigned flag = square_index%2 == 0 ? 1 : -1;
    
    if (relative_position < 0) {
        target = linear_combination(1, _square_coordinates, flag *  abs(relative_position), vertical_direction);
    } else {
        target =  linear_combination(1, _square_coordinates, flag * abs(relative_position), horizontal_direction);
    }
 
    print_result(index, target);

    return 0;
}
