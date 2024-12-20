#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "graph.hpp"

using namespace std;

// função de leitura do grafo
vector<vector<int> > read(string inputFile) {   
    ifstream input(inputFile);
    if (!input) {
        cerr << "Erro ao abrir o arquivo!" << endl;
        exit(1);
    }

    int N; input >> N;
    vector<vector<int> > graph(N);
    int x, y;
    while (input >> x >> y) {
        graph[x].push_back(y);
    }

    return graph;
}


vector<vector<wVertice> > readW(string inputFile) {   
    ifstream input(inputFile);
    if (!input) {
        cerr << "Erro ao abrir o arquivo!" << endl;
        exit(1);
    }

    int N; input >> N;
    vector<vector<wVertice> > graphW(N);
    int x, y, w;
    while (input >> x >> y >> w) {
        wVertice we{y, w};
        graphW[x].push_back(we);
    }

    return graphW;
}


void printW(vector<vector<wVertice> >& graphW, int N) {
    for (int i=0; i < N; ++i) {
        cout << i << ": ";
        for (wVertice wv : graphW[i]) {
            cout << "(" << wv.index << ", "<< wv.cost <<  ")" << " ";
        }
        cout << endl;
    }
}


void print(vector<vector<int> >& graph, int N) {
    for (int i=0; i < N; ++i) {
        cout << i << ": ";
        for (int v : graph[i]) {
            cout << v << " ";
        }
        cout << endl;
    }
}