#include <iostream>
#include <vector>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define INF 0x3f3f3f3f


int N, Pac;
vector<pair<int, int> > items;
vector<vector<pair<int, int> > > mem;

void solve() {
    // Leitura
    cin >> Pac; items.assign(Pac+1, pair<int, int>());
    mem.assign(Pac+1, vector<pair<int, int> >(51, pair<int, int>(0, 0)));
    for (int p=1, q, w; p <= Pac; ++p) {
        cin >> items[p].first >> items[p].second;
    }


    // DP
    for (int item=1; item <= Pac; ++item) {
        int v=items[item].first, w=items[item].second;
        for (int capacity=0, s1, s2; capacity <= 50; ++capacity) {
            if (w > capacity || capacity - w < 0) mem[item][capacity] = mem[item-1][capacity];
            else {
                int s1 = mem[item-1][capacity-w].first + v;
                int s2 = mem[item-1][capacity].first;

                if (s1 >= s2) mem[item][capacity] = make_pair(s1, mem[item-1][capacity-w].second + 1);
                else mem[item][capacity] = mem[item-1][capacity];

            }
        }
    }

    int c2=50, c1=49;
    while (mem[Pac][c2].first == mem[Pac][c1].first) {--c1;--c2;}

    cout << mem[Pac][c2].first << " brinquedos" << endl;
    cout << "Peso: " << c2 << " kg" << endl;
    cout << "sobra(m) " << Pac - mem[Pac][c2].second << " pacote(s)" << endl;
    cout << endl;
}


int main(void) {_
    cin >> N; while(N--) {solve();}
    
    exit(0);
}