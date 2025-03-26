#include <iostream>
#include <map>
#include <queue>
#include <stack>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);

int N;

int main(void) {_
    while(cin >> N) {
        bool q_flag=true, pq_flag=true, s_flag=true, i_flag=false;
        map<int, int> m; 
        queue<int> q; 
        priority_queue<int> pq; 
        stack<int> s;
        
        int cmd, v;
        for (int i=0; i < N; ++i) {
            cin >> cmd >> v;
            if (!i_flag) {
                if (cmd == 1) {m[v]++; q.push(v); pq.push(v); s.push(v);}
                else {
                    if (m.find(v) == m.end() || m.at(v) == 0) {i_flag = true; continue;}
                    if (q_flag) {q_flag = q.front() == v; q.pop();}
                    if (pq_flag) {pq_flag = pq.top() == v; pq.pop();}
                    if (s_flag) {s_flag = s.top() == v; s.pop();}
                }
            }
        }

        if (i_flag) cout << "impossible" << endl;
        else if (q_flag && !pq_flag && !s_flag) cout << "queue" << endl;
        else if (!q_flag && pq_flag && !s_flag) cout << "priority queue" << endl;
        else if (!q_flag && !pq_flag && s_flag) cout << "stack" << endl;
        else cout << "not sure" << endl;  
    }

    exit(0);
}