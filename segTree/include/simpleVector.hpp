//
// Created by João Costa on 03/12/23.
//

#ifndef SIMPLEVECTOR_HPP
#define SIMPLEVECTOR_HPP


#include "matrix.hpp"

class SimpleVector{
    public:
        SimpleVector(int n=0);
        ~SimpleVector();

        void build();
        void update(int i, Matrix* matrix);
        Matrix* query(int i, int j);

        int get_size() {
            return _n;
        }

        Matrix** get_vector() {
            return _vector;
        }

    private:
        int _n;
        Matrix** _vector;

};


#endif //SIMPLEVECTOR_HPP
