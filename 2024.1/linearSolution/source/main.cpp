#include <stdio.h>
#include "fraction.hpp"
#include "equation.hpp"
#include "system.hpp"
#include "utils.hpp"

int main(void) {

    System system; system.read("data/e1.txt");
    system.solve();
}
