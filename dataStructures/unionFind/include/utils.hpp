#ifndef UTILS_HPP
#define UTILS_HPP

inline void swap(int& a, int& b) {
    int temp = b;
    b = a;
    a = temp;
}

#endif