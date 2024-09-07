#ifndef EQUATION_HPP
#define EQUATION_HPP

#include <vector>
#include <sstream>
#include <iomanip>
#include "fraction.hpp"

class Equation {
    public:
        // construtor padrão: equação vazia
        Equation();

        std::string to_string(int length);

        bool is_null();

        // setters and getters
        std::vector<Fraction> get_coefs() const {
            return coefs_;
        }

        Fraction get_coef(int i) const  {
            if (i > dimension_ - 1) {
                printf("Índice fornecido é inválido!\n");
                return Fraction();
            }

            return coefs_[i];
        }


        void set_coef(int i, Fraction fraction) {
            if (i > dimension_ - 1) {
                printf("Índice fornecido é inválido!\n");
                return;
            }

            coefs_[i] = fraction;
        }


        Fraction get_bcoef() const {
            return bcoef_;
        }


        Fraction get_pivot() const {
            if (pivot_pos_ >= dimension_) {return Fraction();} // não há pivot: equação nula
            return coefs_[get_pivot_pos()];
        }

        int get_dimension() const {
            return dimension_;
        }

        int get_pivot_pos() const {
            return pivot_pos_;
        }


        // reconfigura totalmente a equação
        void config(std::vector<Fraction> coefs, Fraction bcoef);

        // multiplica a equação para que o pivot valha 1
        Equation normalize();

        // overload de operadores
        Equation operator+(Equation& e2);
        Equation operator-(Equation& e2);
        Equation operator*(int scalar);
        Equation operator*(Fraction scalar);

    private:
        // número de variáveis
        int dimension_;

        // posição do pivô
        int pivot_pos_;

        // coeficientes das variáveis
        std::vector<Fraction> coefs_;

        // termo independente
        Fraction bcoef_;

};

#endif