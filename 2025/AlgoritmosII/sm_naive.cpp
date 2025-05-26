#include <iostream>
#include <string>

using namespace std;
string T, P;

void naive() {
    int t_sz = T.size(), p_sz = P.size();

    bool match = true;
    for (int s=0; s <= t_sz - p_sz; ++s) {
        
        for (int i=0; i < p_sz; ++i) {
            if (T[s+i] != P[i]) {
                match = false; break;
            }
        }

        if (match) cout << "pattern at " << s << endl;
        else match = true;
    }
}

int main(void) {
    // Leitura do texto e padrão T, P
    cin >> T >> P;

    naive();

    return 0;
}