#include <iostream>
#include <string>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);


string pre_order, in_order;
int N, pt = 0;

string to_pos(string sequence) {  
    int idx = sequence.find(pre_order.at(pt)); int size = sequence.size();
 
    string left = sequence.substr(0, idx);
    string right = sequence.substr(idx+1, size-idx-1);

    if (left.size() > 0) {++pt; left = to_pos(left);}
    if (right.size() > 0) {++pt; right = to_pos(right);}


    return left + right + sequence.at(idx);
}


int main(void) {_
    cin >> N; int n; string ans;
    for (int i=0; i<N; ++i) {
        cin >> n >> pre_order >> in_order;
        ans = to_pos(in_order);
        cout << ans << endl;
        pt = 0;
    }
    
    exit(0);
}