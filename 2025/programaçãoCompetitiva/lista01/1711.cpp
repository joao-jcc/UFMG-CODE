#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define INF 0x3f3f3f3f

int N, M, Q;
vector<vector<pair<int, int>>> listaAdj;
vector<bool> visited;
vector<int> parent, wEdge;
int globalMin;

vector<int> dijkstra(int start) {
    vector<int> dist(N + 1, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;

        for (auto [w, v] : listaAdj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

void dfs(int start, const vector<int>& dist, int targetSize) {
    stack<pair<int, int>> s;
    s.push({start, -1});

    while (!s.empty()) {
        auto [u, p] = s.top();
        s.pop();

        if (visited[u]) continue;
        visited[u] = true;
        parent[u] = p;

        for (auto [w, v] : listaAdj[u]) {
            if (v == p) continue;

            if (!visited[v]) {
                wEdge[v] = w;
                s.push({v, u});
            } else {
                // Ciclo encontrado
                vector<int> ciclo = {v, u};
                int pesoTotal = w;
                int curr = u;

                while (curr != v && curr != -1) {
                    int prev = parent[curr];
                    if (prev == -1) break;

                    pesoTotal += wEdge[curr];
                    ciclo.push_back(prev);
                    curr = prev;
                }

                if (curr == v && pesoTotal >= targetSize) {
                    for (int x : ciclo) {
                        globalMin = min(globalMin, 2 * dist[x] + pesoTotal);
                    }
                }
            }
        }
    }
}

void solve() {
    cin >> N >> M;
    if (cin.eof()) return;

    listaAdj.assign(N + 1, vector<pair<int, int>>());

    for (int i = 0, u, v, w; i < M; ++i) {
        cin >> u >> v >> w;
        listaAdj[u].push_back({w, v});
        listaAdj[v].push_back({w, u});
    }

    cin >> Q;
    for (int i = 0, start, size; i < Q; ++i) {
        cin >> start >> size;
        globalMin = INF;
        vector<int> dist = dijkstra(start);

        visited.assign(N + 1, false);
        parent.assign(N + 1, -1);
        wEdge.assign(N + 1, 0);

        for (int u = 1; u <= N; ++u) {
            if (!visited[u]) {
                dfs(u, dist, size);
            }
        }

        if (globalMin == INF) {
            cout << -1 << endl;
        } else {
            cout << globalMin << endl;
        }
    }
}

int main(void) {_
    while (!cin.eof()) solve();
    
    return 0;
}
