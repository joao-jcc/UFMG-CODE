#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);


unordered_map<char, vector<string>> dig_to_braille = {
    {'1', {"*.", "..", ".."}},
    {'2', {"*.", "*.", ".."}},
    {'3', {"**", "..", ".."}},
    {'4', {"**", ".*", ".."}},
    {'5', {"*.", ".*", ".."}},
    {'6', {"**", "*.", ".."}},
    {'7', {"**", "**", ".."}},
    {'8', {"*.", "**", ".."}},
    {'9', {".*", "*.", ".."}},
    {'0', {".*", "**", ".."}}
};

unordered_map<string, char> braille_to_digit = {
    {"*.....", '1'},
    {"*.*...", '2'},
    {"**....", '3'},
    {"**.*..", '4'},
    {"*..*..", '5'},
    {"***...", '6'},
    {"****..", '7'},
    {"*.**..", '8'},
    {".**...", '9'},
    {".***..", '0'}
};


int D; char L;
string w;

int main(void) {_
    while (true) {
        cin >> D; if (D == 0) break;
        cin >> L;
        if (L == 'S') {
            cin >> w;
            for (int j=0; j < 3; ++j) {
                for (int i=0; i < D-1; ++i) {
                    cout << dig_to_braille.at(w[i])[j] << " ";
                }
                cout << dig_to_braille.at(w[D-1])[j] << endl;
            }
        } else if (L == 'B') {
            vector<string> strs(D, "");
            for (int i=0; i < 3; ++i) {
                for (int j=0; j < D; ++j) {
                    cin >> w; strs[j] += w;
                }
            }
    
            for (int i=0; i < strs.size(); ++i) {
                cout << braille_to_digit.at(strs[i]);
            }
    
            cout << endl;
        }
    }

    exit(0);
}