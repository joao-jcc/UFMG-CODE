#include "fraction.hpp"

Fraction::Fraction(int numerator, int denominator) {
    if (denominator == 0) {
        printf("Denominador deve ser diferente de zero\n");
        exit(1);
    }


    sign_ = denominator * numerator < 0 ? -1 : 1;
    numerator_ = abs(numerator); denominator_ = abs(denominator);
    reduce();
}


Fraction::Fraction() {

}


Fraction::~Fraction() {

}


std::string Fraction::to_string() {
    std::string d = std::to_string(denominator_);
    std::string n = std::to_string(numerator_);

    return sign_ == 1? '+' + n + '/' + d : '-' + n + '/' + d;
}


void Fraction::reduce() {
    if (numerator_ == 0) {
        denominator_ = 1;
    } else {
        int divisor = mdc(numerator_, denominator_);
        denominator_ = denominator_ / divisor;
        numerator_ = numerator_ / divisor;
    }
}


// multiplica fração por fração e retorna Fração resultante
Fraction Fraction::operator*(const Fraction& fraction2) {
    int sign = sign_ * fraction2.get('s');
    return Fraction(numerator_ * fraction2.get('n') * sign, denominator_ * fraction2.get('d'));
}


// multiplica fração por inteiro à direita
Fraction Fraction::operator*(const int number) {
    return (*this) * Fraction(number, 1);
}


// soma fração por inteiro à direita
Fraction Fraction::operator+(int number) {
    return (*this) + Fraction(number, 1);
}


// soma duas frações e retorna a fração resultante
Fraction Fraction::operator+(const Fraction& fraction2) {
    int a = numerator_ * sign_; int b = denominator_;
    int c = fraction2.get('n') * fraction2.get('s'); int d = fraction2.get('d');
 
    int new_numerator = d * a + c * b;
    int new_denominator = b * d;

    return Fraction(new_numerator, new_denominator);
}


// atribui uma fração a outra
Fraction Fraction::operator=(const Fraction& fraction2) {
    numerator_ = fraction2.get('n'); 
    denominator_ = fraction2.get('d');
    sign_ = fraction2.get('s');

    return *this;
}


// compara frações
bool Fraction::operator==(const Fraction& fraction2) const{
    return denominator_ == fraction2.get('d') && numerator_ == fraction2.get('n') && sign_ == fraction2.get('s');
}


Fraction Fraction::operator/(Fraction& fraction2) {
    Fraction fraction_inverted = fraction2.invert();

    return (*this) * fraction_inverted;
}


// subtração fração por inteiro à direita
Fraction Fraction::operator-(int number) {
    return (*this) - Fraction(number, 1);
}


// subtrai duas frações e retorna a fração resultante
Fraction Fraction::operator-(const Fraction& fraction2) {
    Fraction fraction = fraction2;
    return (*this) + (fraction * -1);
}

Fraction Fraction::invert() {
    return Fraction(denominator_ * sign_, numerator_);
}

bool Fraction::is_zero() {
    return numerator_ == 0;
}


void Fraction::parse(std::string coef_str) {

    int numerator, denominator;

    // '/' está contida em coef_str
    size_t pos = coef_str.find('/');
    if (pos != std::string::npos) {

        numerator = std::atoi(coef_str.substr(0, pos).c_str());
        denominator = std::atoi(coef_str.substr(pos+1).c_str()); 

    } else {

        numerator = std::atoi(coef_str.c_str());
        denominator = 1;
        
    }

    *this = Fraction(numerator, denominator);
}