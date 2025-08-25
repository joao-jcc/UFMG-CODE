#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);

/*
N: largura do salão em metros
M: altura do salão em metros
L: largura das tábuas em centímetros
K: número de tábuas
lengths: comprimento das tábuas em metros
*/
int N, M, L, K;
vector<int> lengths;

int min3(int a, int b, int c) {return min(min(a, b), c);}

int main(void) {_

    cin >> N >> M >> L >> K;
    
    // Largura incompatível
    bool n_flag=(N*100) % L == 0, m_flag=(M*100) % L == 0;
    if (!n_flag && !m_flag) {cout << "impossivel" << endl; exit(0);} 

    lengths = vector<int>(max(N, M) + 1, 0);
    for (int i=0, l; i < K; ++i) {cin >> l; ++lengths[l];}

    // Ao longo da altura M
    int spaces=N/L, counter=0, aux=0, half = ceil(M/2);
    if (n_flag) {
        aux = min(lengths[M], spaces); spaces -= aux; counter = aux; 
        for (int l=M-1; l >= half; --l) {
            if (spaces == 0) {break;}

            if (l == half && M%2==0) aux = min((int)(lengths[l]/2), spaces);
            else aux = min3(lengths[l], lengths[M-l], spaces);

            counter += aux*2; spaces-=aux; 
        }

        cout << counter << endl;
    }

    exit(0);
}