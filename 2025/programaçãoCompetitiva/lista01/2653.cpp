#include <iostream>
#include <set>
#include <string>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);

set<string> st;
string seq; int counter = 0;

int main(void) {_ 

    while (cin >> seq) {
        if (st.find(seq) == st.end()) {
            ++counter; st.insert(seq);
        }
    }

    cout << counter << endl;

    exit(0);
}