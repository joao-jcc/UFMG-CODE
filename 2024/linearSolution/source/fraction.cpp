#include "fraction.hpp"

// PUBLIC

Fraction::Fraction() : value_flag_(false) {}


Fraction::Fraction(int numerator, int denominator) {
    if (denominator == 0) {
        printf("Denominador deve ser diferente de zero\n");
        exit(1);
    }


    sign_ = denominator * numerator < 0 ? -1 : 1;
    numerator_ = abs(numerator); denominator_ = abs(denominator);
    reduce_();
    value_flag_ = true;
}


Fraction::~Fraction() {}


void Fraction::parse(std::string fraction_str) {

    int numerator, denominator;

    // '/' está contida em fraction_str
    size_t pos = fraction_str.find('/');
    if (pos != std::string::npos) {

        numerator = std::atoi(fraction_str.substr(0, pos).c_str());
        denominator = std::atoi(fraction_str.substr(pos+1).c_str()); 
    } else {

        numerator = std::atoi(fraction_str.c_str());
        denominator = 1;
        
    }

    *this = Fraction(numerator, denominator);
}


std::string Fraction::to_string() {

    if (!is_valid()) {return std::string();};

    std::string d = std::to_string(denominator_);
    std::string n = std::to_string(numerator_);

    return sign_ == 1? '+' + n + '/' + d : '-' + n + '/' + d;
}


bool Fraction::is_zero() {
    return numerator_ == 0;
}


Fraction Fraction::operator+(int number) const {

    if (!is_valid()) {throw std::invalid_argument("Invalid Fraction in adition");};

    return (*this) + Fraction(number);
}


Fraction Fraction::operator+(const Fraction& fraction2) const{

    if (!is_valid() || !fraction2.is_valid()) {throw std::invalid_argument("Invalid Fraction in adition");};

    int a = numerator_ * sign_; int b = denominator_;
    int c = fraction2.get('n') * fraction2.get('s'); int d = fraction2.get('d');
 
    int new_numerator = d * a + c * b;
    int new_denominator = b * d;

    return Fraction(new_numerator, new_denominator);
}


Fraction Fraction::operator*(const Fraction& fraction2) const {
    if (!is_valid() || !fraction2.is_valid()) {throw std::invalid_argument("Invalid Fraction in multiplication");};
    
    int sign = sign_ * fraction2.get('s');
    return Fraction(numerator_ * fraction2.get('n') * sign, denominator_ * fraction2.get('d'));
}



Fraction Fraction::operator*(const int number) const {
    if (!is_valid()) {throw std::invalid_argument("Invalid Fraction in multiplication");};

    return (*this) * Fraction(number);
}


Fraction Fraction::operator-(int number) const {
    if (!is_valid()) {throw std::invalid_argument("Invalid Fraction in subtraction");};

    return (*this) - Fraction(number, 1);
}


Fraction Fraction::operator-(const Fraction& fraction2) const {
    if (!is_valid() || !fraction2.is_valid()) {throw std::invalid_argument("Invalid Fraction in subtraction");};

    Fraction fraction = fraction2;
    return (*this) + (fraction * -1);
}


Fraction Fraction::operator/(const Fraction& fraction2) const {
    if (!is_valid() || !fraction2.is_valid()) {throw std::invalid_argument("Invalid Fraction in division");};

    Fraction fraction_inverted = fraction2.invert();

    return (*this) * fraction_inverted;
}


Fraction Fraction::operator=(const Fraction& fraction2) {
    if (!fraction2.is_valid()) {throw std::invalid_argument("Invalid Fraction in atribution");};

    numerator_ = fraction2.get('n'); 
    denominator_ = fraction2.get('d');
    sign_ = fraction2.get('s');
    value_flag_ = fraction2.get('v');

    return *this;
}


bool Fraction::operator==(const Fraction& fraction2) const{
    if (!is_valid() || !fraction2.is_valid()) {throw std::invalid_argument("Invalid Fraction in equality comparison");};

    return denominator_ == fraction2.get('d') && numerator_ == fraction2.get('n') && sign_ == fraction2.get('s');
}


Fraction Fraction::invert() const {
    if (!is_valid()) {throw std::invalid_argument("Invalid Fraction in inversion");};

    return Fraction(denominator_ * sign_, numerator_);
}


// GETTERS AND SETTERS
int Fraction::get(char letter) const {
    if (!is_valid()) {throw std::invalid_argument("Invalid Fraction to get values");};

    switch(letter) {
        case 'd':
            return (int)denominator_;
        case 'n':
            return (int)numerator_;
        case 's':
            return sign_;
        case 'v':
            return value_flag_;
        default:
            printf("Entrada Inválida!\n");
            exit(1);
    }
}


bool Fraction::is_valid() const {
    return value_flag_;
}


// PRIVATE

void Fraction::reduce_() {
    if (numerator_ == 0) {
        denominator_ = 1;
    } else {
        int divisor = mdc(numerator_, denominator_);
        denominator_ = denominator_ / divisor;
        numerator_ = numerator_ / divisor;
    }
}
