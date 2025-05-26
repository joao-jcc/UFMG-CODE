#include <iostream>
#include <vector>

using namespace std;

#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define INF 0x3f3f3f3f

int R, C, K;
vector<vector<bool>> matrix;

int getFreeSeats(int r1, int c1, int r2, int c2, const vector<vector<int>>& acc) {
    return acc[r2 + 1][c2 + 1] - acc[r1][c2 + 1] - acc[r2 + 1][c1] + acc[r1][c1];
}

void solve() {
    // Leitura
    matrix.assign(R, vector<bool>(C, false));
    char symb;
    for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
            cin >> symb;
            matrix[r][c] = (symb == '.');
        }
    }

    // Matriz acumulada de prefixos de assentos livres
    vector<vector<int>> matrixAcc(R + 1, vector<int>(C + 1, 0));
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            matrixAcc[i + 1][j + 1] = matrixAcc[i][j + 1] + matrixAcc[i + 1][j] - matrixAcc[i][j] + (matrix[i][j] ? 1 : 0);
        }
    }

    int minArea = INF;

    // Percorrer todos os retângulos possíveis
    for (int r1 = 0; r1 < R; ++r1) {
        for (int r2 = r1; r2 < R; ++r2) {
            // Usar sliding window nas colunas
            int c1 = 0;
            for (int c2 = 0; c2 < C; ++c2) {
                while (c1 <= c2 && getFreeSeats(r1, c1, r2, c2, matrixAcc) >= K) {
                    int area = (r2 - r1 + 1) * (c2 - c1 + 1);
                    minArea = min(minArea, area);
                    ++c1;
                }
            }
        }
    }

    cout << minArea << endl;
}

int main() { _
    while (cin >> R >> C >> K && !(R == 0 && C == 0 && K == 0)) solve();
    return 0;
}
