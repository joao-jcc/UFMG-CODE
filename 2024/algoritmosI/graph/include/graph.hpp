#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct wVertice {
    int index;
    int cost;
};

// função de leitura do grafo
vector<vector<int> > read(string inputFile);

// função de leitura do grafo com pesos
vector<vector<wVertice> > readW(string inputFile);

void print(vector<vector<int> >& graph, int N);
void printW(vector<vector<wVertice> >& graph, int N);

#endif