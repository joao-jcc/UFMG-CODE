#include "graph.hpp"
#include "bfs.hpp"
#include "dfs.hpp"
#include "patrol.hpp"

int main() {
    Graph ggt; BFS bfs(ggt); DFS dfs(ggt); 
    dfs.findBattalions(bfs.capitalDepths, bfs.capital);
    Patrol patrol(bfs, dfs, ggt);

    bfs.print();
    dfs.print();
    patrol.print();
    
    return 0;
}