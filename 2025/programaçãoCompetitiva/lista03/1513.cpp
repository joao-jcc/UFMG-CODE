#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

int n, m, K;
vector<string> bd;

int dx[8] = { 1,  1,  2,  2, -1, -1, -2, -2 };
int dy[8] = { 2, -2,  1, -1,  2, -2,  1, -1 };

int bfs(pair<int,int> src, pair<int,int> dst) {
    
    vector<vector<int>> dist(n, vector<int>(m, -1));
    
    queue<pair<int,int>> q;
    
    dist[src.first][src.second] = 0;
    q.push(src);
    
    while (!q.empty()) {
        
        auto u = q.front();
        q.pop();
        
        int x = u.first;
        int y = u.second;
        
        if (x == dst.first && y == dst.second) {
            return dist[x][y];
        }
        
        for (int d = 0; d < 8; d++) {
            
            int nx = x + dx[d];
            int ny = y + dy[d];
            
            if (nx < 0 || nx >= n ||
                ny < 0 || ny >= m ||
                bd[nx][ny] == '#' ||
                dist[nx][ny] != -1) {
                
                continue;
            }
            
            dist[nx][ny] = dist[x][y] + 1;
            q.push({ nx, ny });
        }
    }
    
    return INT_MAX;
}

int main() {
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    while (true) {
        
        cin >> n >> m >> K;
        
        if (n == 0 && m == 0 && K == 0) {
            break;
        }
        
        bd.resize(n);
        
        for (int i = 0; i < n; i++) {
            cin >> bd[i];
        }
        
        vector<pair<int,int>> pts;
        pair<int,int> start;
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                
                if (bd[i][j] == 'C') {
                    start = { i, j };
                }
                else if (bd[i][j] == 'P') {
                    pts.push_back({ i, j });
                }
            }
        }
        
        int V = K + 1;
        
        vector<vector<int>> d(V, vector<int>(V, INT_MAX));
        
        // dist from start to pawns
        for (int i = 0; i < K; i++) {
            
            d[0][i + 1] = bfs(start, pts[i]);
            d[i + 1][0] = d[0][i + 1];
        }
        
        // dist between pawns
        for (int i = 0; i < K; i++) {
            for (int j = i + 1; j < K; j++) {
                
                int dij = bfs(pts[i], pts[j]);
                
                d[i + 1][j + 1] = dij;
                d[j + 1][i + 1] = dij;
            }
        }
        
        int FULL = (1 << K) - 1;
        const int INF = INT_MAX / 2;
        
        vector<vector<int>> dp(1 << K, vector<int>(K, INF));
        
        // init dp
        for (int i = 0; i < K; i++) {
            int m0 = 1 << i;
            dp[m0][i] = d[0][i + 1];
        }
        
        // dp over subsets
        for (int mask = 0; mask <= FULL; mask++) {
            for (int last = 0; last < K; last++) {
                
                if (!(mask & (1 << last))) {
                    continue;
                }
                
                int cur = dp[mask][last];
                
                if (cur >= INF) {
                    continue;
                }
                
                for (int nxt = 0; nxt < K; nxt++) {
                    
                    if (mask & (1 << nxt)) {
                        continue;
                    }
                    
                    int nm = mask | (1 << nxt);
                    int nd = cur + d[last + 1][nxt + 1];
                    
                    if (nd < dp[nm][nxt]) {
                        dp[nm][nxt] = nd;
                    }
                }
            }
        }
        
        int ans = INF;
        
        for (int i = 0; i < K; i++) {
            int tot = dp[FULL][i] + d[i + 1][0];
            
            if (tot < ans) {
                ans = tot;
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
