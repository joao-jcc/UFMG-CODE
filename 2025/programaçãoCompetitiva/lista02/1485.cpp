#include <iostream>
#include <vector>

using namespace std;

#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define INF 0x3f3f3f3f

int main() { _
    int S, B;
    while (cin >> S >> B && (S || B)) {
        vector<int> X(S), Y(B);
        for (int i = 0; i < S; ++i) cin >> X[i];
        for (int i = 0; i < B; ++i) cin >> Y[i];

        int max_arrecadacao = -INF;

        // Testar todas as rotações da roleta
        for (int start = 0; start < S; ++start) {
            vector<bool> usado(S, false);
            int arrecadacao = 0;
            bool valido = true;

            for (int i = 0; i < B; ++i) {
                int pos1 = (start + 2 * i) % S;
                int pos2 = (pos1 + 1) % S;

                if (usado[pos1] || usado[pos2]) {
                    valido = false;
                    break;
                }

                usado[pos1] = usado[pos2] = true;

                int valor_bola = Y[i] * (X[pos1] + X[pos2]);

                arrecadacao -= valor_bola;
            }

            if (valido) {
                max_arrecadacao = max(max_arrecadacao, arrecadacao);
            }
        }

        cout << max_arrecadacao << endl;
    }

    return 0;
}
