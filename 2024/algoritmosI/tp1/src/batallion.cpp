#include "batallion.hpp"
#include <iostream>
#include <vector>
#include <stack>


void InfoK::print() {
    std::cout << "nComponents: " << nComponents << std::endl;

    std::cout << "COMPONENTS: " << std::endl;
    for (int v=0; v < components.size(); ++v) {
        std::cout << v << ": " << components[v] << std::endl;
    }
}


InfoK kosaraju(const std::vector<std::vector<int> >& graph, const std::vector<std::vector<int> >& graph_t, int N) {
    std::vector<bool> explored(N, false);
    std::vector<int> components(N, -1);
    std::stack<int> deathOrder;
    

    for (int v=0; v < N; ++v) {
        if (!explored[v]) {
            dfsDeathOrder(graph, v, explored, deathOrder);
        }
    }

    int componentIndex = 0;
    std::fill(explored.begin(), explored.end(), false);

    while(!deathOrder.empty()) {

        int start = deathOrder.top(); deathOrder.pop();

        if (!explored[start]) {
            dfsSCC(graph_t, start, componentIndex, explored, components);
            ++componentIndex;
        }

    }

    return InfoK{componentIndex, components};
}


void dfsDeathOrder(const std::vector<std::vector<int> >& graph, 
            int start, std::vector<bool>& explored, 
            std::stack<int>& deathOrder) {
    
    explored[start] = true; 
    for (int u : graph[start]) {
        
        if (!explored[u]) {
            dfsDeathOrder(graph, u, explored, deathOrder);
        }
    }
    
    deathOrder.push(start);
}


void dfsSCC(const std::vector<std::vector<int> >& graph, 
            int start, int& componentIndex, 
            std::vector<bool>& explored, 
            std::vector<int>& components) {
    
    explored[start] = true; components[start] = componentIndex;
    for (int u : graph[start]) {
        if (!explored[u]) {
            dfsSCC(graph, u, componentIndex, explored, components);
        }
    }
}


std::vector<int> getBatallions(InfoCapital infoc, InfoK infok) {
    // capital está em uma das SCC: logo são nComponents - 1 batalhões
    std::vector<int> batallions(infok.nComponents, -1); int N = infoc.depths.size();
    for (int component=0; component < infok.nComponents; ++component) {

        int batallion = -1; int minDepth = INT_MAX;
        for (int v=0; v < N; ++v) {

            if (infok.components[v] == component && infoc.depths[v] < minDepth) {
                batallion = v; minDepth = infoc.depths[v];
            }

        }
        if (batallion == infoc.capital) {continue;}
        batallions[component] = batallion;
    }

    return batallions;
}