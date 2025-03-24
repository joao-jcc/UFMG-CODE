#include <iostream>
#include <vector>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define INF 0x3f3f3f3f

/*
N: largura do salão em metros
M: altura do salão em metros
L: largura das tábuas em centímetros
K: número de tábuas
lengths: comprimento das tábuas em metros
*/
int N, M, L, K;

int min3(int a, int b, int c) {return min(min(a, b), c);}

int to_count(int w, int h, vector<int>& lengths) {
    if ((w*100) % L == 0) {
        int spaces = (w*100) / L, tabuas=0;
        for (int l = h; l >= (h>>1)+1; --l) {
            int  aux = min3(lengths[l], lengths[h-l], spaces);
            tabuas = l == h ? tabuas + aux : tabuas + 2*aux; spaces -= aux;
            if (spaces == 0) {break;}
        }

        if (h%2 == 0 && spaces != 0) {
            int aux = min(lengths[h/2]>>1, spaces); 
            tabuas += 2*aux; spaces-=aux;
        }    

        if (spaces == 0) {return tabuas;}
    }

    return INF;
}

int main(void) {_
    while (true) {
        cin >> N >> M; if (N == 0 && M ==0) break; cin >> L >> K;
        vector<int> lengths(max(N, M) + 1, 0); lengths[0] = K;
        for (int i = 0, l; i < K; ++i) {cin >> l; if (l <= max(N, M)) ++lengths[l];}

        int tabuas = min(to_count(N, M, lengths), to_count(M, N, lengths));
        
        if (tabuas == INF) {
            cout << "impossivel" << endl;
        } else {
            cout << tabuas << endl;
        }
    }

    exit(0);
}