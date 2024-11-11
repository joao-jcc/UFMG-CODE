// batallion.hpp

#ifndef BATALLION_HPP
#define BATALLION_HPP

#include <vector>
#include <stack>
#include "capital.hpp"

struct InfoK {
    int nComponents;
    std::vector<int> components;

    void print();
};

void dfsDeathOrder(const std::vector<std::vector<int> >& graph, 
            int start, std::vector<bool>& explored, 
            std::stack<int>& deathOrder);

void dfsSCC(const std::vector<std::vector<int> >& graph, 
            int start, int& componentIndex,
            std::vector<bool>& explored, 
            std::vector<int>& components);


InfoK kosaraju(const std::vector<std::vector<int> >& graph, const std::vector<std::vector<int> >& graph_t, int N);

std::vector<int> getBatallions(InfoCapital infoc, InfoK infok);

std::vector<int> patrol(std::vector<int> batallions);


#endif // BATALLION_HPP
