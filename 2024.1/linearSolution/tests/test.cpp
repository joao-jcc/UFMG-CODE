#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"

#include "fraction.hpp"
#include "equation.hpp"
#include "utils.hpp"

// FRACTION

TEST_CASE("Getters and Setters [Fraction]") {
    Fraction f1 = Fraction(2, 4);

    CHECK_EQ(f1.get('n'), 2);
    CHECK_EQ(f1.get('d'), 4);
    CHECK_EQ(f1.get('s'), 1);
}


TEST_CASE("Sign [Fraction]") {
    Fraction f1 = Fraction(2, -4);

    CHECK_EQ(f1.get('n'), 2);
    CHECK_EQ(f1.get('d'), 4);
    CHECK_EQ(f1.get('s'), -1);

   Fraction f2 = Fraction(-10, -2);

    CHECK_EQ(f2.get('n'), 10);
    CHECK_EQ(f2.get('d'), 2);
    CHECK_EQ(f2.get('s'), 1);

   Fraction f3 = Fraction(0, -2);

    CHECK_EQ(f3.get('n'), 0);
    CHECK_EQ(f3.get('d'), 2);
    CHECK_EQ(f3.get('s'), 1);

}


TEST_CASE("Reduce [Fraction]") {
    Fraction f1 = Fraction(2, -4);
    f1.reduce();

    CHECK_EQ(f1.get('n'), 1);
    CHECK_EQ(f1.get('d'), 2);
    CHECK_EQ(f1.get('s'), -1);

   Fraction f2 = Fraction(0, -2);
   f2.reduce();

    CHECK_EQ(f2.get('n'), 0);
    CHECK_EQ(f2.get('d'), 1);
    CHECK_EQ(f2.get('s'), 1);

   Fraction f3 = Fraction(-112, -4);
   f3.reduce();

    CHECK_EQ(f3.get('n'), 28);
    CHECK_EQ(f3.get('d'), 1);
    CHECK_EQ(f3.get('s'), 1);

}


TEST_CASE("Operator= [Fraction]") {
   Fraction f1 = Fraction(2, 4);
   Fraction f2 = Fraction(1, 2);

   // f1 recebe f2
   f1 = f2;

   CHECK_EQ(f1.get('n'), f2.get('n'));
   CHECK_EQ(f1.get('d'), f2.get('d'));
   CHECK_EQ(f1.get('s'), f2.get('s'));
   CHECK(f1 == f2);
}


TEST_CASE("Operator== [Fraction]") {
   Fraction f1 = Fraction(2, 4);
   Fraction f2 = Fraction(1, 2);
   CHECK_EQ(f1 == f2, false);
}


TEST_CASE("Operator+ [Fraction]") {
   Fraction f1 = Fraction(1, 2);
   Fraction f2 = Fraction(1, 3);

   Fraction f3 = f1 + f2; // (1/2) + (1/3)

   CHECK_EQ(5, f3.get('n'));
   CHECK_EQ(6, f3.get('d'));
   CHECK_EQ(1, f3.get('s'));

   Fraction f4 = Fraction(1, -2);
   Fraction f5 = Fraction(3, 30);

   Fraction f6 = f4 + f5; // (-1/2) + (3/30)
   
   CHECK_EQ(24, f6.get('n'));
   CHECK_EQ(60, f6.get('d'));
   CHECK_EQ(-1, f6.get('s'));

   Fraction f7 = Fraction(0, 1);

   Fraction f8 = f4 + f7; // (-1/2) + 0
   
   CHECK_EQ(1, f8.get('n'));
   CHECK_EQ(2, f8.get('d'));
   CHECK_EQ(-1, f8.get('s'));

   Fraction f9 = f4 + 5; // (-1/2) + 5
   CHECK_EQ(9, f9.get('n'));
   CHECK_EQ(2, f9.get('d'));
   CHECK_EQ(1, f9.get('s'));
}

TEST_CASE("Operator- [Fraction]") {
   Fraction f1 = Fraction(1, 2);
   Fraction f2 = Fraction(1, 3);

   Fraction f3 = f1 - f2; // (1/2) - (1/3)

   CHECK_EQ(1, f3.get('n'));
   CHECK_EQ(6, f3.get('d'));
   CHECK_EQ(1, f3.get('s'));

   Fraction f4 = Fraction(1, -2);
   Fraction f5 = Fraction(3, 30);

   Fraction f6 = f4 - f5; // (-1/2) - (3/30)
   
   CHECK_EQ(36, f6.get('n'));
   CHECK_EQ(60, f6.get('d'));
   CHECK_EQ(-1, f6.get('s'));

   Fraction f7 = Fraction(0, 1);

   Fraction f8 = f4 - f7; // (-1/2) - 0
   
   CHECK_EQ(1, f8.get('n'));
   CHECK_EQ(2, f8.get('d'));
   CHECK_EQ(-1, f8.get('s'));

   Fraction f9 = f4 - 5; // (-1/2) - 5
   CHECK_EQ(11, f9.get('n'));
   CHECK_EQ(2, f9.get('d'));
   CHECK_EQ(-1, f9.get('s'));
}

TEST_CASE("Operator* [Fraction]") {
   Fraction f1 = Fraction(1, 2);
   Fraction f2 = Fraction(1, 3);

   Fraction f3 = f1 * f2; // (1/2) * (1/3)

   CHECK_EQ(1, f3.get('n'));
   CHECK_EQ(6, f3.get('d'));
   CHECK_EQ(1, f3.get('s'));

   Fraction f4 = Fraction(1, -2);
   Fraction f5 = Fraction(3, 30);

   Fraction f6 = f4 * f5; // (-1/2) * (3/30)
   
   CHECK_EQ(3, f6.get('n'));
   CHECK_EQ(60, f6.get('d'));
   CHECK_EQ(-1, f6.get('s'));

   Fraction f7 = Fraction(0, 1);

   Fraction f8 = f4 * f7; // (-1/2) * (0/1)
   
   CHECK_EQ(0, f8.get('n'));
   CHECK_EQ(2, f8.get('d'));
   CHECK_EQ(1, f8.get('s'));

   Fraction f9 = f4 * 5; // (-1/2) * 5
   CHECK_EQ(5, f9.get('n'));
   CHECK_EQ(2, f9.get('d'));
   CHECK_EQ(-1, f9.get('s'));

   Fraction f10 = f9 * 0; // (-1/2) * 0
   CHECK_EQ(0, f10.get('n'));
   CHECK_EQ(2, f10.get('d'));
   CHECK_EQ(1, f10.get('s'));
}


TEST_CASE("operator+ [Equation]") {
   Fraction f1 = Fraction(2, 3);
   Fraction f2 = Fraction(-1, -3);
   Fraction f3 = Fraction(0, 1);
   Fraction f4 = Fraction(5, -5);
   Fraction f5 = Fraction(-3, 4);
   Fraction f6 = Fraction(3, 2);

   std::vector<Fraction> coefs1 = {f1, f2};
   Fraction bcoef1 = f3;


   std::vector<Fraction> coefs2 = {f4, f5};
   Fraction bcoef2 = f6;

   Equation e1; e1.config(coefs1, bcoef1); // (2/3)x0 + (1/3)x1 = (0/1)
   Equation e2; e2.config(coefs2, bcoef2); // (-5/5)x0 + (-3/4)x1 = (3/2)

   Equation e3 = e1 + e2;
   std::vector<Fraction> coefs3 = e3.get_coefs();
   Fraction bcoef3 = e3.get_bcoef();

   CHECK_EQ(bcoef3 == Fraction(3, 2), true);
   CHECK_EQ(coefs3[0] == Fraction(-5, 15), true);
   CHECK_EQ(coefs3[1] == Fraction(-5, 12), true);
}


TEST_CASE("operator* [Equation]") {
   Fraction f1 = Fraction(2, 3);
   Fraction f2 = Fraction(-1, 3);
   Fraction f3 = Fraction(0, 1);


   std::vector<Fraction> coefs1 = {f1, f2};
   Fraction bcoef1 = f3;

   Equation e1; e1.config(coefs1, bcoef1); // (2/3)x0 + (-1/3)x1 = (0/1)


   // int scalar
   Equation e2 = e1 * -2;
   std::vector<Fraction> coefs2 = e2.get_coefs();
   Fraction bcoef2 = e2.get_bcoef();

   CHECK_EQ(bcoef2 == Fraction(0, 1), true);
   CHECK_EQ(coefs2[0] == Fraction(-4, 3), true);
   CHECK_EQ(coefs2[1] == Fraction(2, 3), true);

   // Fraction scalar
   Equation e3 = e1 * Fraction(2, -3);
   std::vector<Fraction> coefs3 = e3.get_coefs();
   Fraction bcoef3 = e3.get_bcoef();

   CHECK_EQ(bcoef3 == Fraction(0, 3), true);
   CHECK_EQ(coefs3[0] == Fraction(-4, 9), true);
   CHECK_EQ(coefs3[1] == Fraction(2, 9), true);

}


TEST_CASE("operator- [Equation]") {
   Fraction f1 = Fraction(2, 3);
   Fraction f2 = Fraction(-1, -3);
   Fraction f3 = Fraction(0, 1);
   Fraction f4 = Fraction(5, -5);
   Fraction f5 = Fraction(-3, 4);
   Fraction f6 = Fraction(3, 2);

   std::vector<Fraction> coefs1 = {f1, f2};
   Fraction bcoef1 = f3;


   std::vector<Fraction> coefs2 = {f4, f5};
   Fraction bcoef2 = f6;

   Equation e1; e1.config(coefs1, bcoef1); // (2/3)x0 + (1/3)x1 = (0/1)
   Equation e2; e2.config(coefs2, bcoef2); // (-5/5)x0 + (-3/4)x1 = (3/2)

   Equation e3 = e1 - e2;
   std::vector<Fraction> coefs3 = e3.get_coefs();
   Fraction bcoef3 = e3.get_bcoef();

   CHECK_EQ(bcoef3 == Fraction(-3, 2), true);
   CHECK_EQ(coefs3[0] == Fraction(25, 15), true);
   CHECK_EQ(coefs3[1] == Fraction(13, 12), true);
}

