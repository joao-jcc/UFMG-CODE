#include <iostream>
#include <string>
#include <map>

using namespace std;
string T, P;
vector<vector<int> > sigma;
map<char, int> alphabet;

bool is_sufix(const string& p, const string& t) {
    if (p.size() > t.size()) return false;
    return t.substr(t.size() - p.size()) == p;
}



void build_sigma() {
    int m = P.size(); 
    for (int q=0; q <= m; ++q) {
        for (auto [c, id] : alphabet) {
            int k = min(m+1, q+2);

            do {
                --k;
            } while (!is_sufix( P.substr(0, k),  P.substr(0, q) + c));

            sigma[q][id] = k;

        }
    }
}


void print_sigma() {
    cout << "  ";
    for (auto [c, id] : alphabet) cout << c << " ";
    cout << endl;

    for (int q=0; q <= P.size(); ++q) {
        cout << q << " ";

        for (auto [c, id] : alphabet) {
            cout << sigma[q][id] << " ";
        }
        cout << endl;
    }
}

int main(void) {
    // Leitura do texto e padrão T, P
    cin >> T >> P;
    
    int id = 0;
    for (char c : T) {
        if (alphabet.find(c) != alphabet.end()) continue;
        else alphabet[c] = id;
        ++id;
    }

    for (auto [c, id] : alphabet) {
        cout << c << ": " << id << endl;
    }

    sigma.assign(P.size()+1, vector<int>(id+1, 0));

    build_sigma();
    print_sigma();

    return 0;
}