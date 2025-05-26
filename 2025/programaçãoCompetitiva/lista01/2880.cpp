#include <iostream>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);

string code, word;

int main(void) {_
    cin >> code >> word;
    int counter=0, ws = word.size(), cs = code.size();

    for (int i=0; i <= cs - ws ; ++i) {
        bool flag = true;
        for (int j=0; j < ws; ++j) {
            if (word[j] == code[i+j]) {flag=false; break;}
        }
        counter += flag ? 1 : 0;
    }

    cout << counter << endl;

    exit(0);
}