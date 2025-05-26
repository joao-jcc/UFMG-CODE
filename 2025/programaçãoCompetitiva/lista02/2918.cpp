#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define MOD 1000000007

string num;
int dp[20][2][200];

int digitDP(int pos, bool tight, int sum) {
    if (pos == num.size()) return sum;
    if (dp[pos][tight][sum] != -1) return dp[pos][tight][sum];

    int limit = tight ? num[pos] - '0' : 9;
    int res = 0;

    for (int d = 0; d <= limit; ++d) {
        bool newTight = tight && (d == limit);
        res = (res + digitDP(pos + 1, newTight, sum + d)) % MOD;
    }

    return dp[pos][tight][sum] = res;
}

int sum_digits(long long x) {
    num = to_string(x);
    for (int i = 0; i < 20; ++i)
        for (int j = 0; j < 2; ++j)
            for (int k = 0; k < 200; ++k)
                dp[i][j][k] = -1;
    
    
    return digitDP(0, 1, 0);
}

void solve() {
    long long L, R;
    while (cin >> L >> R) {
        int ans = (sum_digits(R) - sum_digits(L - 1) + MOD) % MOD;
        cout << ans << endl;
    }
}

int main() { _
    solve();
    return 0;
}
