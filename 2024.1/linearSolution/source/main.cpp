#include <stdio.h>
#include "fraction.hpp"
#include "equation.hpp"
#include "system.hpp"

int main(void) {
    Fraction f1 = Fraction(1, 1);
    Fraction f2 = Fraction(3, 1);
    Fraction f3 = Fraction(6, 1);
    Fraction f4 = Fraction(5, 1);

    Fraction f5 = Fraction(2, 1);
    Fraction f6 = Fraction(6, 1);
    Fraction f7 = Fraction(12, 1);
    Fraction f8 = Fraction(10, 1);

    Fraction f9 = Fraction(4, 1);
    Fraction f10 = Fraction(7, 1);
    Fraction f11 = Fraction(-3, 1);
    Fraction f12 = Fraction(2, 1);

    std::vector<Fraction> coefs1 = {f1, f2, f3};
    Fraction bcoef1 = f4;


    std::vector<Fraction> coefs2 = {f5, f6, f7};
    Fraction bcoef2 = f8;

    std::vector<Fraction> coefs3 = {f9, f10, f11};
    Fraction bcoef3 = f12;

    Equation e1; e1.config(coefs1, bcoef1);
    Equation e2; e2.config(coefs2, bcoef2);
    Equation e3; e3.config(coefs3, bcoef3);

    System system;
    system.add(e1); system.add(e2); system.add(e3);

    system.solve();
}
