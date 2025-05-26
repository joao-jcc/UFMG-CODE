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

        // Busca binária
        int hmax = max_ti, hmin=1, hcurr;
        bool sucess;
        while (hmax - hmin > 0) {
            
            hcurr = (hmax + hmin + 1) / 2;
        
            // À direita e à esquerda
            sucess = true;
            for (int dx=1; dx < hcurr; ++dx) {
                if (highs[c + dx] < hcurr - dx || highs[c - dx] < hcurr - dx) {
                    sucess = false; break;
                }
            }
    
            if (sucess) hmin = hcurr;
            else hmax = hcurr-1;
        }

        max_t = max(max_t, hmax); // altere o triângulo máximo
    }

    cout << max_t << endl;

    exit(0);
}