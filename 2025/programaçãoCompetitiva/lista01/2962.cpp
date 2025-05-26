#include <iostream>
#include <vector>
#include <queue>


using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define INF 0x3f3f3f3f


int M, N, S;
int xmin=INF, ymin=INF, xmax=-1, ymax=-1;
vector<vector<int> > sensors;
vector<bool> explored;


bool update(int s) {
    int x = sensors[s][0], y = sensors[s][1], r = sensors[s][2];
    if (x-r < xmin) xmin = x-r;
    if (x+r > xmax) xmax = x+r;
    if (y-r < ymin) ymin = y-r;
    if (y+r > ymax) ymax = y+r;

       if ((xmin <= 0 && ymin <= 0) || (xmax >= M && ymax >= N) || (xmin <= 0 && xmax >= M) || (ymin <= 0 && ymax >= N)) {
        return true;
    } else {
        return false;
    }
}


bool connected(int s1, int s2) {
    int x1 = sensors[s1][0], y1 = sensors[s1][1], r1 = sensors[s1][2];
    int x2 = sensors[s2][0], y2 = sensors[s2][1], r2 = sensors[s2][2];


    return (r1+r2)*(r1+r2) >= (y2-y1)*(y2-y1) + (x2-x1)*(x2-x1);

}


int main(void) {_

    // Leitura
    cin >> M >> N >> S;
    sensors.assign(S, vector<int>(3)); explored.assign(S, false);
    for (int k=0; k < S; ++k) {
        // x, y, raio
        cin >> sensors[k][0] >> sensors[k][1] >> sensors[k][2];
    }

    // Busca
    for (int root=0; root < S; ++root) {
        if (explored[root]) continue;
 
        queue<int> q; q.push(root); explored[root] = true;
        if (update(root)) {cout << 'N' << endl; exit(0);}

        while (!q.empty()) {
            int current = q.front(); q.pop();
            
            for (int s=0; s < S; ++s) {
                if (!explored[s] && connected(current, s)) {
                    q.push(s); explored[s] = true;
                    if (update(s)) {cout << 'N' << endl; exit(0);}
                }
            } 
        }

        // Reset
        xmin=INF; ymin=INF; xmax=-1; ymax=-1;

    }

    cout << 'S' << endl; exit(0);
}