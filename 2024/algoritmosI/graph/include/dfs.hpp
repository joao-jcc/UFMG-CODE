#ifndef DFS_HPP
#define DFS_HPP

#include <iostream>
#include <stack>

struct Node {
    int parent;
    int born;
    int death;
    int color;

    void print() {
        std::cout << "p=" << parent << "(" << born << "/" << death << ")" << std::endl;
    }
}


std::vector<int> dfs(const std::vector<std::vector<int> >& graph, int start) {
    int N = graph.size();
    std::vector<Color> colors(N, WHITE);
    std::vector<int> parents(N, -1);

    std::queue<int> s;
    s.push(start);
    colors[start] = GRAY;

    while (!s.empty()) {
        int v = s.front();
        s.pop();

        for (int u : graph[v]) {
            if (colors[u] == WHITE) {
                s.push(u);
                parents[u] = v;
                colors[u] = GRAY;
            }
        }
    }

    return parents;
}




#endif