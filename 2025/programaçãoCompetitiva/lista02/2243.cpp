#include <iostream>
#include <vector>


using namespace std;
#define _ ios_base::sync_with_stdio(0);cin.tie(0);

int H;
vector<int> highs;

int min3(int a, int b, int c) {
    return min(min(a, b), c);
}

int main(void) {_
    // Leitura
    cin >> H; highs.assign(H, 0);
    for (int i=0; i < H; ++i) cin >> highs[i];

    int max_t = 0;
    for (int c=0; c < H; ++c) {
        int max_ti = min3(c+1, H-c, highs[c]);
        if (max_ti <= max_t) continue; // Próxima coluna

        // Para todas as alturas possíveis na coluna C
        for (int h=max_ti; h > 0; --h) {
            // Alturas abaixo de h corrente não servem
            if (h <= max_t) break; 

            // À direita e à esquerda
            bool flag = true;
            for (int dx=1; dx < h; ++dx) {
                if (highs[c + dx] < h - dx || highs[c - dx] < h - dx) {
                    flag = false; break;
                }
            }

            if (flag) max_t = max(max_t, h); // altere o triângulo máximo
        }
    }

    cout << max_t << endl;

    exit(0);
}