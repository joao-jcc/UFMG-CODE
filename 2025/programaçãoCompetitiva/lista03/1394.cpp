#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

const int MAXV = 900;
const int MAXE = 20000;
int head[MAXV], to[MAXE], cap[MAXE], revv[MAXE], nxt[MAXE], ec;
int lvl[MAXV], ptr[MAXV];
int s, t;

void ae(int u, int v, int c) {
    to[ec]   = v;
    cap[ec]  = c;
    revv[ec] = ec + 1;
    nxt[ec]  = head[u];
    head[u]  = ec++;
    
    to[ec]   = u;
    cap[ec]  = 0;
    revv[ec] = ec - 1;
    nxt[ec]  = head[v];
    head[v]  = ec++;
}

bool bfs() {
    fill(lvl, lvl + t + 1, -1);
    lvl[s] = 0;

    queue<int> q;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int e = head[u]; e != -1; e = nxt[e]) {
            int v = to[e];
            
            if (lvl[v] < 0 && cap[e] > 0) {
                lvl[v] = lvl[u] + 1;
                q.push(v);
            }
        }
    }

    return lvl[t] >= 0;
}

int dfs(int u, int f) {
    if (u == t || f == 0) 
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

int flow() {
    int res = 0;

    while (bfs()) {
        for (int i = 0; i <= t; i++) {
            ptr[i] = head[i];
        }

        int pushed;
        while ((pushed = dfs(s, 1e9)) > 0) {
            res += pushed;
        }
    }

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (true) {
        int N, M, G;
        cin >> N >> M >> G;

        if (!N && !M && !G) 
            break;

        vector<int> sct(N, 0);
        vector<vector<int>> played(N, vector<int>(N, 0));

        for (int i = 0; i < G; i++) {
            int a, b;
            char c;
            cin >> a >> c >> b;

            if (c == '<') {
                sct[b] += 2;
            }
            else if (c == '=') {
                sct[a]++;
                sct[b]++;
            }

            played[a][b]++;
            played[b][a]++;
        }

        int rem0 = 0;
        for (int j = 1; j < N; j++) {
            rem0 += M - played[0][j];
        }

        int s0 = sct[0] + 2 * rem0;
        bool ok = true;

        for (int i = 1; i < N; i++) {
            if (sct[i] > s0 - 1) {
                ok = false;
                break;
            }
        }

        if (!ok) {
            cout << "N\n";
            continue;
        }

        vector<pair<int,int>> matchs;
        for (int i = 1; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                int r = M - played[i][j];
                if (r > 0) {
                    matchs.emplace_back(i, j);
                }
            }
        }

        int P = matchs.size();
        s = 0;
        t = P + (N - 1) + 1;
        
        for (int i = 0; i <= t; i++) {
            head[i] = -1;
        }
        ec = 0;

        for (int k = 0; k < P; k++) {
            int i = matchs[k].first;
            int j = matchs[k].second;
            int cp = 2 * (M - played[i][j]);

            ae(s, 1 + k, cp);
            ae(1 + k, 1 + P + (i - 1), cp);
            ae(1 + k, 1 + P + (j - 1), cp);
        }

        for (int i = 1; i < N; i++) {
            int capi = s0 - 1 - sct[i];
            ae(1 + P + (i - 1), t, capi);
        }

        int tot = 0;
        for (int k = 0; k < P; k++) {
            tot += 2 * (M - played[matchs[k].first][matchs[k].second]);
        }

        cout << (flow() == tot ? "Y\n" : "N\n");
    }

    return 0;
}
