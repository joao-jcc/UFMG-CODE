#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <algorithm>
#include "equation.hpp"

class System {
    public:
        System();
        ~System();

        void print();

        void add(Equation& equation);

        void sort();

    private:
        std::vector<Equation> equations_;

};

#endif