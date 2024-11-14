#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include "graph.hpp"
#include "bfs.hpp"
#include "dfs.hpp"
#include "patrol.hpp"

int main() {
    for (int i = 1; i <=8; ++i) {
        // Construir o caminho do arquivo com zeros à esquerda (e.g., "input01.txt")
        std::ostringstream filename; filename << "data/teste/inputs/testCase0" << i << ".txt";

        Graph ggt(filename.str());

        BFS bfs(ggt);
        DFS dfs(ggt); dfs.findBattalions(bfs.capitalDepths, bfs.capital);

        Patrol patrol(bfs, dfs, ggt);

        bfs.print();
        dfs.print();
        patrol.print();

    }
    
    return 0;
}
