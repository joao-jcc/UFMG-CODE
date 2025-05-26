#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define INF 0x3f3f3f3f


long int N, C, T, low, high;
vector<long int> pops; 

long int compute_c(long int max_pop) {
    long int acc = 0, c = 1;
    for (long int i=0; i < pops.size(); ++i) {
        if (max_pop < acc + pops[i]) {
            acc = 0; ++c;
        } 
        
        acc += pops[i];
    }

    return c;
}

int main(void) {_
    // Leitura
    cin >> N >> C >> T;
    pops.assign(N, 0);
    low = high = 0;
    for (long int i=0, v; i < N; ++i) {
        cin >> v;
        low = max(low, v);
        high += v;
        pops[i] = v;
    }


    // Busca binária
    while (low < high) {
        long int mid = (low + high) / 2.0;
        if (compute_c(mid) > C) low = mid + 1;
        else high = mid;
    }

    cout << (low + T - 1) / T << endl;

    exit(0);
}