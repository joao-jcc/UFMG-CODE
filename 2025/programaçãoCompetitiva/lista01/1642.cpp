#include <iostream>
#include <vector>
#include <string>
#include <map>



using namespace std;
#define _ ios_base::sync_with_stdio(0);cin.tie(0);

int m, ans; string s;
map<char, int> mp;

int main(void) {_
    cin >> m >> s;

    int i=0, j=0, l = 0, ans=-1;
    while (j < s.size()) {
        // conta numero de caracteres distintos e comprimento da substring.
        int uniq = 0;

        // Move ponteiro da direita
        while (uniq < m && j < s.size()) {
            // caractere novo
            if (mp.find(s[j]) == mp.end()) ++uniq;
            
            ++mp[s[j]]; ++j; ++l;
        }

        // atualiza comprimento máximo
        ans = ans < l-1 ? l-1 : ans;

        // Move ponteiro da esquerda
        while (uniq > m && j < s.size()) {
            if (mp[s[i]] == 1) --uniq;

            --mp[s[i]]; ++i; --l;
        }
    }

    cout << ans << endl;
    exit(0);
}