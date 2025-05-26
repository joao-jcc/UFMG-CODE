#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define _ ios_base::sync_with_stdio(0); cin.tie(0);

int long_string(string a, string b) {
    int n = a.size(), m = b.size();
    vector<vector<int> > dp(2, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; ++i) {

        int cur = i % 2, prev = 1 - cur;

        for (int j = 1; j <= m; ++j) {

            if (a[i - 1] == b[j - 1])
                dp[cur][j] = dp[prev][j - 1] + 1;
            else
                dp[cur][j] = max(dp[cur][j - 1], dp[prev][j]);

        }
    }

    return dp[n % 2][m];
}


int main() { _
    string s1, s2;
    cin >> s1 >> s2;
    cout << long_string(s1, s2) << '\n';
    return 0;
}
