#include "equation.hpp"

Equation::Equation() 
: dimension_(0), coefs_(std::vector<Fraction>()), bcoef_(Fraction()), pivot_pos_(-1), description_(std::string()) {

}


Equation::Equation(std::vector<Fraction>& coefs, Fraction& bcoef) {
    config(coefs, bcoef);
}


void Equation::config(std::vector<Fraction> coefs, Fraction bcoef) {
    dimension_ = coefs.size();
    coefs_ = coefs;
    bcoef_ = bcoef;
    for (int i=0; i < dimension_; ++i) {
        if (!coefs_[i].is_zero()) {pivot_pos_ = i; return;}
    }
    pivot_pos_ = dimension_; // coeficientes todos nulos
}


std::string Equation::to_string(int length) {
    std::stringstream result;

    for (int i = 0; i < dimension_; ++i) {
        std::stringstream coef_stream;
        
        // Align the fraction to the left with a fixed width
        coef_stream << std::left << std::setw(length) << coefs_[i].to_string();

        // Add the variable directly after the fraction with consistent spacing
        if (i != dimension_ - 1) {
            result << coef_stream.str();
        } else {
            // Last term (before the equals sign)
            result << coef_stream.str() << " | " << std::left << std::setw(length) << bcoef_.to_string();
        }
    }

    return result.str();
}


bool Equation::is_null() {
    return pivot_pos_ >= dimension_;
}


Equation Equation::normalize() {
    // equação nula não tem pivô: retorna equação vazia
    if (is_null()) {Equation();}

    Fraction factor = coefs_[pivot_pos_].invert();

    // retorna equação normalizada
    return (*this) * factor;

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
    e3.set_description(*this, e2); // DESCRIÇÃO DA EQUAÇÃO

    return e3;
}


Equation Equation::operator-(Equation& e2) {
    Equation e3 = e2 * -1;
    return (*this) + e3;
}


// operador* para equação multiplicada pro escalar (fração ou inteiro)
Equation Equation::operator*(int scalar) {
    Fraction scalar_fraction = Fraction(scalar, 1);

    return (*this) * scalar_fraction;
}


Equation Equation::operator*(Fraction scalar) {
    std::vector<Fraction> coefs_result;
    for (int i=0; i < dimension_; ++i) {
        coefs_result.push_back(coefs_[i] * scalar);
    }

    Fraction bcoef_result = bcoef_ * scalar;

    Equation e_result; e_result.config(coefs_result, bcoef_result);
    e_result.set_description(*this, scalar); // DESCRIÇÃO DA EQUAÇÃO

    return e_result;
}

void Equation::parse(std::string line_equation) {
    std::string parsed;
    std::stringstream line_stream(line_equation);

    std::vector<Fraction> coefs; Fraction bcoef;
    while(getline(line_stream, parsed, ' ')) {
        if (parsed == "|") {
            getline(line_stream, parsed, ' ');
            Fraction fraction; fraction.parse(parsed);
            bcoef = fraction;
        } else {
            Fraction fraction; fraction.parse(parsed);
            coefs.push_back(fraction);
        }
    }

    config(coefs, bcoef);
}