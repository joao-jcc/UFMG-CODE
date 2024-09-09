#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <algorithm>
#include <string>
#include <fstream>
#include "equation.hpp"

class System {
    public:
        System();
        ~System();

        void read();
        void read(std::string path);

        void print(std::string separator="", int max_coef_length=6);

        void add(Equation& equation);

        void sort();

        void solve();

    private:
        int count_equations_;
        std::vector<Equation> equations_;

};

#endif