#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <algorithm>
#include "equation.hpp"

class System {
    public:
        System();
        ~System();

        void print(std::string separator="", int max_coef_length=6);

        void add(Equation& equation);

        void sort();

        void solve();

    private:
        std::vector<Equation> equations_;

};

#endif