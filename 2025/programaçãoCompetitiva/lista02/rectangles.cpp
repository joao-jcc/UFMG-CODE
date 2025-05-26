#include <iostream>

#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define INF 0x3f3f3f3f

using namespace std;

int mem[501][501];
int A, B;

int main() {
    cin >> A >> B;

    for (int i = 1; i <= A; ++i) {
        for (int j = 1; j <= B; ++j) {
            // Quadrado sem cortes
            if (i == j) mem[i][j] = 0; 
            else {

                mem[i][j] = INF;
                // Corte horizontal
                for (int k = 1; k < i; ++k) mem[i][j] = min(mem[i][j], mem[k][j] + mem[i - k][j] + 1);
                
                // Corte vertical
                for (int k = 1; k < j; ++k) mem[i][j] = min(mem[i][j], mem[i][k] + mem[i][j - k] + 1);

            }
        }
    }

    cout << mem[A][B] << endl;

    exit(0);
}