#include <iostream>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);

string N;

int main(void) {_
    cin >> N; 
    
    int acc = 0;
    for (int i=0; i < N.size(); ++i) {
        acc +=  (int)N[i] % 3;  
    }

    cout << acc % 3 << endl;


    exit(0);
}