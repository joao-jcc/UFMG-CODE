#include "utils.hpp"

int mdc(int a, int b) {
    if (a == 0) {return b;}
    if (b == 0) {return a;}

    int divisor = a < b ? a : b;

    while (a % divisor != 0 || b % divisor != 0) {
        --divisor;
    }

    return divisor;
}