#include <iostream>
#include <vector>
#include <queue>
#include <bits/stdc++.h>

using namespace std;

int N, V, E;
vector<vector<char> > graph;
vector<bool> explored;

int main(void) {
    cin >> N;

    for (int i=1; i<=N; ++i) {
        cout << "Case #" << i << ":" << endl;

        cin >> V >> E;
        graph = vector<vector<char> >(V, vector<char>()); // lista de adjacência
        explored = vector<bool>(V, false);

        // Leitura do grafo
        for (int l=0; l<E; ++l) {
            char u, v; cin >> u >> v; u-='a'; v-='a';
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        // BFS
        queue<char> q; int ncomponents = 0;
        for (char origin=0; origin < V; ++origin) {
            if (!explored[origin]) {
                q.push(origin); vector<char> component;
                
                while (!q.empty()) {
                    char u = q.front(); q.pop(); explored[u] = true; component.push_back(u);
                    for (int i=0; i < graph[u].size(); ++i) {
                        char v = graph[u][i];
                        if (!explored[v]) { q.push(v); explored[v] = true;}
                    }
                }
                
                sort(component.begin(), component.end());
                for (int i=0; i < component.size(); ++i) {
                    cout << char(component[i] + 'a') << ',';
                }

                cout << endl; ++ncomponents;
            }
        }
        cout << ncomponents << " connected components" << endl;
        cout << endl;
    }

    return 0;
}