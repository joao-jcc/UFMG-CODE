#ifndef EQUATION_HPP
#define EQUATION_HPP

#include <vector>
#include <sstream>
#include "fraction.hpp"

class Equation {
    public:
        // construtor padrão: equação vazia
        Equation();

        std::string to_string(int length=0);

        bool is_null();

        // setters and getters
        std::vector<Fraction> get_coefs() const {
            return coefs_;
        }

        Fraction get_bcoef() const {
            return bcoef_;
        }

        int get_dimension() const {
            return dimension_;
        }

        int get_pivot() const {
            return pivot_;
        }

        // reconfigura totalmente a equação
        void config(std::vector<Fraction> coefs, Fraction bcoef);

        // overload de operadores
        Equation operator+(Equation& e2);
        Equation operator-(Equation& e2);
        Equation operator*(int scalar);
        Equation operator*(Fraction scalar);

    private:
        // número de variáveis
        int dimension_;

        // posição do pivô
        int pivot_;

        // coeficientes das variáveis
        std::vector<Fraction> coefs_;

        // termo independente
        Fraction bcoef_;
};

#endif