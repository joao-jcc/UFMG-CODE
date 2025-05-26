#include <iostream>
#include <vector>
using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);



const int MAX = 1000;
int seq[MAX];
int dp[MAX][MAX][2];

int main() { _
    int N;
    while (cin >> N && N) {
        int len = 2 * N;
        for (int i = 0; i < len; i++) cin >> seq[i];

        // zera dp
        for (int i = 0; i < len; i++)
            for (int j = 0; j < len; j++)
                dp[i][j][0] = dp[i][j][1] = 0;

        for (int l = 1; l <= len; l++) {
            for (int i = 0; i + l - 1 < len; i++) {
                int j = i + l - 1;
                for (int player = 0; player <= 1; player++) {
                    if (i == j) {
                        if (player == 0 && seq[i] % 2 == 0)
                            dp[i][j][player] = 1;
                        else
                            dp[i][j][player] = 0;
                    } else {
                        if (player == 0) {
                            int left = (seq[i] % 2 == 0 ? 1 : 0) + dp[i + 1][j][1];
                            int right = (seq[j] % 2 == 0 ? 1 : 0) + dp[i][j - 1][1];
                            dp[i][j][player] = max(left, right);
                        } else {
                            int left = dp[i + 1][j][0];
                            int right = dp[i][j - 1][0];
                            dp[i][j][player] = min(left, right);
                        }
                    }
                }
            }
        }

        cout << dp[0][len - 1][0] << endl;
    }

    return 0;
}
