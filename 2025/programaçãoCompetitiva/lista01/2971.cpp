#include <iostream>
#include <vector>
#include <map>

using namespace std;

#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define INF 0x3f3f3f3f

map<char, int> mp = {
    {'A', 0}, {'2', 1}, {'3', 2}, {'4', 3}, {'5', 4},
    {'6', 5}, {'7', 6}, {'8', 7}, {'9', 8}, {'D', 9},
    {'Q', 10}, {'J', 11}, {'K', 12}
};

int N, K, player;
vector<vector<int> > hands;
int winner = -1;

void turn() {
    // Jogador tem o coringa e pode descartá-lo
    if (hands[player][13] && hands[player][14]) {
        hands[player][13] = 0; hands[player][14] = 0;
        // Verifica se o jogador é o vencedor
        for (int s=0; s < 13; ++s) {
            if (hands[player][s] == 4) winner = player;
        }
        player = (player+1)%N;
        hands[player][13] = 1; hands[player][14] = 0;
    }

    else {
        // Jogador tem o coringa mas não pode descartá-lo
        if (hands[player][13] && !hands[player][14]) hands[player][14] = 1;

        // Descarta a carta de menor valor
        int min_freq = INF, min_symb = -1;
        for (int s=0; s < 13; ++s) {
            int freq = hands[player][s];
            if (freq > 0 && freq < min_freq) {
                min_freq = freq; min_symb = s;
            }
        }

        --hands[player][min_symb];

        // verifica se o jogador é o vencedor
        for (int s=0; s < 13; ++s) {
            if (hands[player][s] == 4) winner = player;
        }

        player = (player+1)%N;
        ++hands[player][min_symb];
    }
}

void check_winner() {
    int win=-1, win_symb = INF;
    for (int p=0; p < N; ++p) {
        for (int s=0; s < 13; ++s) {
            if (hands[p][s] == 4 && s < win_symb && hands[p][13] == 0) {
                win = p; win_symb = s;
            }
        }
    }

    winner = win;
}

int main(void) {_
    cin >> N >> K;
    hands.assign(N, vector<int>(15, 0)); // 13 símbolos + wildcard + wildcard_flag
    player = K-1;
    hands[player][13] = 1; 
    hands[player][14] = 0; // Coringa não pode ser descartado

    char symb;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < 4; ++j) {
            cin >> symb;
            hands[i][mp[symb]]++;
        }
    }

    check_winner();

    while(winner == -1) turn();


    cout << winner + 1 << endl;

    return 0;
}
