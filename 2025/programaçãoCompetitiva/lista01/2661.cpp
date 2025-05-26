#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);

long int N;
vector<bool> crivo;

bool is_prime(int v) {
    if (v < 2) return false;
    int sv = (int) sqrt(v);
    for (int i=2; i <= sv; ++i) {
        if (v%i == 0) {return false;}
    }
    return true;
}

int main(void) {_
    cin >> N;

    // Raiz quadrada ?
    int SN = (int) sqrt(N);

    // Calcula Crivo de Erastótenes
    crivo.assign(SN+1, true);
    for (int v=2; v <= SN; ++v) {
        if (crivo[v]) {
            int mult = 2;
            while (v * mult <= SN) {
                crivo[v*mult] = false;
                ++mult;
            }  
        }
    }

    // Calcula numero de primos distintos divisores de N
    int count = 0;
    for (int v=2; v <= SN; ++v) {
        if (crivo[v] && (N%v  == 0)) {
            ++count;
            while (N % v == 0) {N /= v;}
        }
        if (N <= 1) {break;}
    }

    if (is_prime(N)) ++count;

    int ans = (1 << count) - count - 1;

    cout << ans << endl;

    exit(0);
}