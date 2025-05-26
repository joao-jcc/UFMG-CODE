#include <iostream>
#include <vector>

using namespace std;

#define _ ios_base::sync_with_stdio(0); cin.tie(0);

// Estado corrente
int N, M;
vector<vector<int>> matrix;
vector<pair<int, int>> positions;

int directions[4][2] = {{2, 2}, {-2, -2}, {2, -2}, {-2, 2}}; 

// Caminhamento máximo partindo de uma dada posição
int walk(int x0, int y0) {
    int result = 0;

    for (int i = 0; i < 4; ++i) {
        int dx = directions[i][0], dy = directions[i][1];
        
        if (x0 + dx < N && x0 + dx >= 0 && y0 + dy < M && y0 + dy >= 0 &&
            matrix[x0 + dx / 2][y0 + dy / 2] == 2 && matrix[x0 + dx][y0 + dy] == 0) {

            matrix[x0][y0] = 0;
            matrix[x0 + dx / 2][y0 + dy / 2] = 0;
            matrix[x0 + dx][y0 + dy] = 1;

            result = max(result, walk(x0 + dx, y0 + dy) + 1);

            matrix[x0][y0] = 1;
            matrix[x0 + dx / 2][y0 + dy / 2] = 2;
            matrix[x0 + dx][y0 + dy] = 0;
        }
    }

    return result;
}

int main(void) {_
    while (true) {
        cin >> N >> M; if (N == 0 && M == 0) break;
        matrix.clear(); positions.clear();
        matrix.assign(N, vector<int>(M, -1));

        bool flag = true; int j;
        for (int i = N - 1; i >= 0; --i) {
            
            j = flag ? 0 : 1;

            for (; j < M; j += 2) {
                cin >> matrix[i][j];
                if (matrix[i][j] == 1) positions.push_back(make_pair(i, j));
            }
            flag = !flag;
        }

        int result = 0;
        for (pair<int, int> p : positions) {
            result = max(result, walk(p.first, p.second));
        }

        cout << result << endl;
    }

    return 0;
}
