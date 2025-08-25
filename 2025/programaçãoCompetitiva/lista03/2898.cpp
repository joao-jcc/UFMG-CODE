#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXV = 55;
const int MAXE = 10000;
const int INF = 1000000000;

int head[MAXV], to[MAXE], cap[MAXE], revv[MAXE], nxt[MAXE], ec;
int lvl[MAXV], ptr[MAXV];
int src, sink;

void add_edge(int u, int v, int c) {
    to[ec] = v; cap[ec] = c; revv[ec] = ec+1; nxt[ec] = head[u]; head[u] = ec++;
    to[ec] = u; cap[ec] = 0; revv[ec] = ec-1; nxt[ec] = head[v]; head[v] = ec++;
}

bool bfs() {
    fill(lvl, lvl + sink + 1, -1);
    queue<int> q;
    lvl[src] = 0;
    q.push(src);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int e = head[u]; e != -1; e = nxt[e]) {
            int v = to[e];
            if (lvl[v] < 0 && cap[e] > 0) {
                lvl[v] = lvl[u] + 1;
                q.push(v);
            }
        }
    }
    return lvl[sink] >= 0;
}

int dfs(int u, int f) {
    if (u == sink || f == 0)
        return f;

    for (int &e = ptr[u]; e != -1; e = nxt[e]) {
        int v = to[e];
        if (lvl[v] == lvl[u] + 1 && cap[e] > 0) {
            int w = dfs(v, min(f, cap[e]));
            if (w > 0) {
                cap[e]       -= w;
                cap[revv[e]] += w;
                return w;
            }
        }
    }
    return 0;
}

int maxflow() {
    int flow = 0;
    while (bfs()) {
        for (int i = 0; i <= sink; i++) {
            ptr[i] = head[i];
        }
        int pushed;
        while ((pushed = dfs(src, INF)) > 0) {
            flow += pushed;
        }
    }
    return flow;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, A;
    while ( (cin >> N >> M >> A) ) {
        if (N==0 && M==0 && A==0) break;

        vector<int> U(M), V(M), S(M);
        for (int i = 0; i < M; i++) {
            cin >> U[i] >> V[i] >> S[i];
        }

        src  = 1;
        sink = N;

        int ans = 0;
        for (int days = 1; days <= A; days++) {

            for (int i = 1; i <= N; i++) {
                head[i] = -1;
            }
            ec = 0;

            for (int i = 0; i < M; i++) {
                int c = days * S[i];
                add_edge(U[i], V[i], c);
            }

            int f = maxflow();
            if (f >= A) {
                ans = days;
                break;
            }
        }

        cout << ans << "\n";
    }

    return 0;
}
