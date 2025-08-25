#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>


using namespace std;
const int INF = 1e9;


struct E { int v, c, r; };

struct Dinic {
    int N, S, T;
    vector<vector<E>> g;
    vector<int> lvl, ptr;
    queue<int> q;

    Dinic(int n, int s, int t): N(n), S(s), T(t) {
        g.assign(N, {});
        lvl.assign(N, 0);
        ptr.assign(N, 0);
    }

    void add(int u, int v, int c) {
        g[u].push_back({v, c, (int)g[v].size()});
        g[v].push_back({u, 0, (int)g[u].size()-1});
    }

    bool bfs() {
        fill(lvl.begin(), lvl.end(), -1);
        lvl[S] = 0;
        q = queue<int>();
        q.push(S);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto &e : g[u]) {
                if (lvl[e.v] < 0 && e.c > 0) {
                    lvl[e.v] = lvl[u] + 1;
                    q.push(e.v);
                }
            }
        }


        return lvl[T] >= 0;
    }


    int dfs(int u, int f) {
        if (!f || u == T) return f;

        for (int &i = ptr[u]; i < (int)g[u].size(); i++) {
            auto &e = g[u][i];
            if (lvl[e.v] == lvl[u] + 1 && e.c > 0) {
                int w = dfs(e.v, min(f, e.c));
                if (w) {
                    e.c -= w;
                    g[e.v][e.r].c += w;
                    return w;
                }
            }
        }


        return 0;
    }


    int maxf() {

        int flow = 0;
        while (bfs()) {
            fill(ptr.begin(), ptr.end(), 0);
            while (int pushed = dfs(S, INF))
                flow += pushed;
        }


        return flow;
    }
};

int idx(const string &s) {

    if (s == "XXL") return 0;
    if (s == "XL")  return 1;
    if (s == "L")   return 2;
    if (s == "M")   return 3;
    if (s == "S")   return 4;
    return 5; // XS

}

int main(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tc;
    cin >> tc;
    while (tc--) {
        
        int N, M;
        cin >> N >> M;
        int per = N / 6;
        int SRC = 0;
        int VOL = 1;
        int SIZ = VOL + M;
        int SNK = SIZ + 6;
        Dinic D(SNK+1, SRC, SNK);

        for (int i = 0; i < M; i++) {
            D.add(SRC, VOL + i, 1);
            string a, b;
            cin >> a >> b;
            D.add(VOL + i, SIZ + idx(a), 1);
            D.add(VOL + i, SIZ + idx(b), 1);
        }
        for (int i = 0; i < 6; i++) {
            D.add(SIZ + i, SNK, per);
        }

        int f = D.maxf();
        cout << (f == M ? "YES\n" : "NO\n");
    }

    return 0;
}
