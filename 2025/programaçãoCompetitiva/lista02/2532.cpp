#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define INF 0x3f3f3f3f

int N, P;
vector<int> dano, mana;

void solve() {
    dano.assign(N + 1, 0);
    mana.assign(N + 1, 0);

    int total_dano = 0;
    for (int i = 1; i <= N; ++i) {
        cin >> dano[i] >> mana[i];
        total_dano += dano[i];
    }

    vector<vector<int>> dp(N + 1, vector<int>(total_dano + 1, INF));
    dp[0][0] = 0;

    for (int i = 1; i <= N; ++i) {
        int m = mana[i], d = dano[i];
        for (int j = 0; j <= total_dano; ++j) {
            if (d > j) dp[i][j] = dp[i-1][j];
            else dp[i][j] = min(dp[i-1][j], dp[i - 1][j - dano[i]] + mana[i]);        
        }
    }

    int ans = INF;
    for (int j = P; j <= total_dano; ++j) {
        ans = min(ans, dp[N][j]);
    }

    if (ans == INF) cout << "-1" << endl;
    else cout << ans << endl;
}

int main() {_
    while (cin >> N >> P)
        solve();
    return 0;
}
