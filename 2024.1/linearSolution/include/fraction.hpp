#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <stdio.h>
#include <iostream>
#include <string>
#include "utils.hpp"

class Fraction {
    public:
        Fraction();
        Fraction(int numerator, int denominator=1);
        ~Fraction();

        void reduce();

        std::string to_string();
        void parse(std::string coef_str); // reconstroi o objeto

        bool is_zero();

        Fraction operator+(const Fraction& fraction2);
        Fraction operator+(int number);
        // frações resultantes nulas mantém denominador; caso sejão reduzidas o denominador fica igual a 1
        Fraction operator*(const Fraction& fraction2);
        Fraction operator*(const int number);
        Fraction operator-(const Fraction& fraction2);
        Fraction operator-(int number);
        Fraction operator=(const Fraction& fraction2);
        bool operator==(const Fraction& fraction2) const;
        Fraction operator/(Fraction& fraction2);
        Fraction invert();


        // getters and setters
        int get(char letter) const {
            switch(letter) {
                case 'd':
                    return (int)denominator_;
                case 'n':
                    return (int)numerator_;
                case 's':
                    return sign_;
                default:
                    printf("Entrada Inválida!\n");
                    exit(1);
            }
        }
    
    private:
        unsigned numerator_;
        unsigned denominator_;
        int sign_;
};

#endif