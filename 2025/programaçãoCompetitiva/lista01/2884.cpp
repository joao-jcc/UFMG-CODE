#include <iostream>
#include <vector>
#include <set>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);


vector<vector<int> > interruptores;
vector<bool> lampadas;

int N, M, L;


int main(void) {_
    cin >> N >> M >> L; interruptores = vector<vector<int>>(N, vector<int>()); lampadas = vector<bool>(M+1, false);
    int l;
    for (int i=0; i<L; ++i) {cin >> l; lampadas[l] = true;}

    for (int i=0; i<N; ++i) {
        int K; cin >> K;
        for (int j=0; j<K; ++j) {cin >> l; interruptores[i].push_back(l);}
    }

    int counter=0, interruptor=0;
    for (; counter < N+N; ++counter) {
        if (L == 0) {cout << counter << endl; exit(0);}
        interruptor = counter % N;
        for (int l : interruptores[interruptor]) {
            if (lampadas[l]) {lampadas[l] = 0; --L;} else {lampadas[l] = 1; ++L;}
        }
    }

    cout << -1 << endl;

    exit(0);
}


/*
OBSERVAÇÃO
As lâmpadas retornam ao estado inicial após 2N acionamentos dos interruptores em sequência. 
Isso ocorre pois teremos número par trocas de sinal para cada lâmpada, após 2N acionamentos.
*/