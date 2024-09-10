#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <stdio.h>
#include <iostream>
#include <string>
#include "utils.hpp"

class Fraction {
    public:
        // construtor padrão
        Fraction();

        // construtor numérico
        Fraction(int numerator, int denominator=1);

        // destrutor
        ~Fraction();

        // reconstroi a fração a partir de uma string, ex.: "a/b"
        void parse(std::string fraction_str);

        // representão da fração em string
        std::string to_string();

        // verifica se a fração é nula
        bool is_zero();

        // OVERLOAD DE OPERADORES

        // soma
        Fraction operator+(const Fraction& fraction2) const;
        Fraction operator+(int number) const;

        // operador multiplicativo
        Fraction operator*(const Fraction& fraction2) const;
        Fraction operator*(const int number) const;

        // subtração: cominação do operador multiplitivo e aditivo
        Fraction operator-(const Fraction& fraction2) const;
        Fraction operator-(int number) const;

        // divisão
        Fraction operator/(const Fraction& fraction2) const;

        // atribuição
        Fraction operator=(const Fraction& fraction2);

        // comparação de igualdade
        bool operator==(const Fraction& fraction2) const;

        // inversão
        Fraction invert() const;

        // Validation
        bool is_valid() const;


        // GETTERS AND SETTERS
        int get(char letter) const;

    
    private:
        unsigned numerator_;
        unsigned denominator_;
        int sign_;

        // indica se a fração tem valores
        bool value_flag_;

        // minimiza a fraçao
        void reduce_();
};

#endif