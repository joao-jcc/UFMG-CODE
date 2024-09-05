#include "equation.hpp"

Equation::Equation() 
: dimension_(0), coefs_(std::vector<Fraction>()), bcoef_(Fraction()), pivot_(-1) {

}


void Equation::config(std::vector<Fraction> coefs, Fraction bcoef) {
    dimension_ = coefs.size();
    coefs_ = coefs;
    bcoef_ = bcoef;
    for (int i=0; i < dimension_; ++i) {
        if (!coefs_[i].is_zero()) {pivot_ = i; return;}
    }
    pivot_ = dimension_; // coeficientes todos nulos
}


std::string Equation::to_string(int length) {
    std::stringstream result;

    for (int i = 0; i < dimension_; ++i) {
        std::stringstream coef_stream;
        coef_stream.width(length);  // Define o comprimento do campo
        coef_stream << coefs_[i].to_string();

        if (i != dimension_ - 1) {
            result << coef_stream.str() << " x" << (i + 1) << " + ";
        } else {
            result << coef_stream.str() << " x" << (i + 1) << " = " << bcoef_.to_string();
        }
    }

    return result.str();
}


bool Equation::is_null() {
    return pivot_ >= dimension_;
}

// OVERLOAD DE OPERADORES
Equation Equation::operator+(Equation& e2) {
    if (dimension_ != e2.get_dimension()) {
        printf("Dimensões não são compatíveis!\n");
        exit(1);
    }

    std::vector<Fraction> coefs_e2 = e2.get_coefs();
    Fraction bcoef_e2 = e2.get_bcoef();

    std::vector<Fraction> coefs_result;
    for (int i=0; i < dimension_; ++i) {
        coefs_result.push_back(coefs_e2[i] + coefs_[i]);
    }

    Fraction bcoef_result = bcoef_ + bcoef_e2;

    Equation e3; e3.config(coefs_result, bcoef_result);

    return e3;
}


Equation Equation::operator-(Equation& e2) {
    Equation e3 = e2 * -1;
    return (*this) + e3;
}

// operador* para equação multiplicada pro escalar (fração ou inteiro)
Equation Equation::operator*(int scalar) {
    std::vector<Fraction> coefs_result;
    for (int i=0; i < dimension_; ++i) {
        coefs_result.push_back(coefs_[i] * scalar);
    }

    Fraction bcoef_result = bcoef_ * scalar;

    Equation e_result; e_result.config(coefs_result, bcoef_result);

    return e_result;
}

Equation Equation::operator*(Fraction scalar) {
    std::vector<Fraction> coefs_result;
    for (int i=0; i < dimension_; ++i) {
        coefs_result.push_back(coefs_[i] * scalar);
    }

    Fraction bcoef_result = bcoef_ * scalar;

    Equation e_result; e_result.config(coefs_result, bcoef_result);

    return e_result;
}