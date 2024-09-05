#include <stdio.h>
#include "fraction.hpp"
#include "equation.hpp"
#include "system.hpp"

int main(void) {
    Fraction f1 = Fraction(0, 5);
    Fraction f2 = Fraction(-3, 4);
    Fraction f3 = Fraction(0, 1);
    Fraction f4 = Fraction(0, -5);
    Fraction f5 = Fraction(-3, 4);
    Fraction f6 = Fraction(3, 2);

    std::vector<Fraction> coefs1 = {f1, f2, f4};
    Fraction bcoef1 = f3;


    std::vector<Fraction> coefs2 = {f4, f5, f3};
    Fraction bcoef2 = f6;

    Equation e1; e1.config(coefs1, bcoef1);
    Equation e2; e2.config(coefs2, bcoef2);
    Equation e3 = e1 - e2;

    System system;
    system.add(e1); system.add(e2); system.add(e3);

    system.print();
}
