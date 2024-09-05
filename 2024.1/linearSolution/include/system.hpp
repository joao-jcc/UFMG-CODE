#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <algorithm>
#include "equation.hpp"

class System {
    public:
        System();
        ~System();

        void print(std::string separator, int max_coef_length=6, int max_operation_length=15);

        void add(Equation& equation);

        void sort();

        void pivot_to_one(int index);

        void solve(bool print_flag);

    private:
        std::vector<Equation> equations_;

};

#endif