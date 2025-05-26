#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);

vector<vector<pair<int, int> > > adj; int N;
struct CompareMin {
    bool operator()(pair<int, int> a, pair<int, int> b) {
        return a.second > b.second;
    }
};

struct CompareMax {
    bool operator()(pair<int, int> a, pair<int, int> b) {
        return a.second < b.second;
    }
};

priority_queue<pair<int, int>, vector<pair<int, int>>, CompareMin> pq_min;
priority_queue<pair<int, int>, vector<pair<int, int>>, CompareMax> pq_max;
vector<bool> explored;

int main(void) {_

    // Leitura do grafo
    cin >> N; int max_node = -1;
    for (int i=0, u, v, w; i < N; ++i) {
        cin >> u >> v >> w; int new_max = max(max(max_node, u), v);
        if (max_node < new_max) {max_node=new_max; adj.resize(max_node+1);}

        adj[u].push_back(make_pair(v, w)); adj[v].push_back(make_pair(u, w));
    }
    
    
    // Árvore geradora mínima
    explored = vector<bool>(max_node+1, false); pq_min.push(make_pair(max_node, 0)); int count_exp=0, min_cost=0;
    while (count_exp < max_node) {
        pair<int, int> pu = pq_min.top(); pq_min.pop(); if (explored[pu.first]) continue;
        min_cost += pu.second;  ++count_exp; explored[pu.first] = true;
        for (pair<int, int> pv : adj[pu.first]) {if (!explored[pv.first]) pq_min.push(pv);}
        
    }


    // Árvore geradora máxima
    explored = vector<bool>(max_node+1, false); pq_max.push(make_pair(max_node, 0)); count_exp=0; int max_cost=0;
    while (count_exp < max_node) {
        pair<int, int> pu = pq_max.top(); pq_max.pop(); if (explored[pu.first]) continue;

        max_cost += pu.second;  ++count_exp; explored[pu.first] = true;
        for (pair<int, int> pv : adj[pu.first]) {if (!explored[pv.first]) pq_max.push(pv);}
        
    }

    cout << max_cost << endl; cout << min_cost << endl;

    exit(0);
}