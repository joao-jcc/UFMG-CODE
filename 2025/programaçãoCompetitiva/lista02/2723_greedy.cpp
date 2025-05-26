#include <iostream>
#include <vector>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define INF 0x3f3f3f3f

int T;
vector<int> gifts;

void solve() {
    // Leitura
    int N;
    cin >> N; gifts.assign(N, 0);
    for (int i=0; i < N; ++i) cin >> gifts[i];

    int state = 0; bool ans = true;
    for (int gift : gifts) {
        // Adiciona presente no lado mais pesado
        if (gift + state <= 5) state += gift;

        // Adiciona presente no lado menos pesado
        else if (abs(gift-state) <= 5) state = abs(gift - state);

        // Não é possível adicionar presente em nenhum dos lados
        else {ans=false; break;}
    }

    if (ans) cout << "Feliz Natal!" << endl;
    else cout << "Ho Ho Ho!" << endl;
}


int main(void) {_
    cin >> T; while(T--) {solve();}
    
    exit(0);
}