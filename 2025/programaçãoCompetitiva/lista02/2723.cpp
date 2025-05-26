#include <iostream>
#include <vector>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define INF 0x3f3f3f3f

int T, N;
vector<int> gifts;
vector<vector<int> > mem;

bool search(int state, int i) {
    if (mem[state][i] != -1) return mem[state][i];

    int acc = gifts[i] + state;
    int dcc = abs(gifts[i] - state);

    // Não é possível adicionar o presente
    if (acc > 5 && dcc > 5) { mem[state][i] = 0; return false;}
    
    // Último item
    if (i == N-1 && (i == acc <= 5 || dcc <= 5)) { mem[state][i] = 1; return true;}

    bool s1 = false, s2 = false;
    // Incrementa o desbalanceamento
    if (acc <= 5) s1 = search(acc, i+1);

    // Decrementa o desbalanceamento
    if (dcc <= 5 && i != 0) s2 = search(dcc, i+1);
    
    if (s1 || s2) mem[state][i] = 1;
    return s1 || s2;
}

void solve() {
    // Leitura
    cin >> N; gifts.assign(N, 0); mem.assign(6, vector<int>(N, -1));
    for (int i=0; i < N; ++i) cin >> gifts[i];

    int ans = search(0, 0);

    if (ans) cout << "Feliz Natal!" << endl;
    else cout << "Ho Ho Ho!" << endl;
}


int main(void) {_
    cin >> T; while(T--) {solve();}
    
    exit(0);
}