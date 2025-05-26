#include <iostream>
#include <vector>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);


long long count_sub_seq(int n, int k, const vector<int>& seq) {
    vector<vector<long long>> dp(n, vector<long long>(k + 1, 0));

    for (int i = 0; i < n; ++i)
        dp[i][1] = 1;

    for (int len = 2; len <= k; ++len) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (seq[j] < seq[i])
                    dp[i][len] += dp[j][len - 1];
            }
        }
    }

    long long total = 0;
    for (int i = 0; i < n; ++i)
        total += dp[i][k];

    return total;
}


int main() {_
    int n, k;
    while (cin >> n >> k && (n || k)) {

        vector<int> seq(n);
        for (int i = 0; i < n; ++i)
            cin >> seq[i];
        cout << count_sub_seq(n, k, seq) << endl;
    }

    return 0;
}
