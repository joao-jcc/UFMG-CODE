#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define MAXN 1005

int N, K;
vector<int> P, C;
double dp[MAXN][MAXN];
bool computed[MAXN][MAXN];

double solve(int i, int k) {
    if (i == N) return 0.0;
    if (computed[i][k]) return dp[i][k];

    double &res = dp[i][k];
    computed[i][k] = true;

    // Tentar responder a pergunta i
    double prob = C[i] / 100.0;
    double try_answer = prob * (P[i] + solve(i + 1, k));

    // Pular a pergunta i (se possível)
    double skip = -1;
    if (k > 0)
        skip = P[i] + solve(i + 1, k - 1);

    res = max(try_answer, skip);
    return res;
}


int main() {_
    while (cin >> N >> K) {
        P.resize(N);
        C.resize(N);
        for (int i = 0; i < N; ++i) cin >> P[i];
        for (int i = 0; i < N; ++i) cin >> C[i];

        // Limpa a memória
        for (int i = 0; i <= N; ++i)
            for (int j = 0; j <= K; ++j)
                computed[i][j] = false;

        cout << fixed << setprecision(2) << solve(0, K) << endl;
    }
    return 0;
}
