#include <iostream>
#include <vector>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);

bool reverse_is_equal(vector<int>& entry, vector<int>& out, int n) {
    for (int i=0; i < n; ++i) {
        if (entry[n-1-i] != out[i]) return false;
    }
    return true;
}

vector<int> dobra_l(vector<int>& entry, int d, int n) {
    vector<int> result(n-d);
    for (int i=0; i < d; ++i) result[i] = entry[i] + entry[2*d - 1 - i];
    for (int i=0; i < n - 2*d; ++i) result[d+i] = entry[2*d + i];

    return result;
}

vector<int> dobra_r(vector<int>& entry, int d, int n) {
    vector<int> result(d);
    for (int i=0; i < n-2*(n-d); ++i) result[d-i-1] = entry[i];
    for (int i=0; i < n-d; ++i) result[i] = entry[d-i-1] + entry[d+i];

    return result; 
}



bool solve_aux(vector<int>& entry, vector<int>& out) {
    int entry_sz = entry.size(), out_sz = out.size();
    // entrada do mesmo tamanho da saída
    if (entry_sz == out_sz) {
        return entry == out || reverse_is_equal(entry, out, entry_sz);
    }

    // entrada maior que a saída: dobra em todas as posicões válidas
    for (int d=1; d < entry_sz; ++d) {
        if (max(entry_sz-d, d) < out_sz) continue;
        // resultado tem tamanho >= ao de result
        vector<int> result;
        if (d <= entry_sz-d) result = dobra_l(entry, d, entry_sz);
        else result = dobra_r(entry, d, entry_sz);
        

        if (solve_aux(result, out)) return true;
    }
    return false;
}

 
int main(void) {_
    int N, M;
    while(cin >> N) {
        vector<int> entry(N);  for (int i=0; i < N; ++i) cin >> entry[i];
        cin >> M; 
        vector<int> out(M); for (int i=0; i < M; ++i) cin >> out[i];
    
        bool ans = solve_aux(entry, out);
        if (ans) cout << 'S' << endl;
        else cout << 'N' << endl;

    }
    
    exit(0);
}