#include <iostream>
#include <vector>
#include <queue>


using namespace std;
const int INF = 1e9;

struct E { int v, c, r; };
int S, T;

vector<vector<E>> g;
vector<int> lvl, ptr;
queue<int> q;

void add(int u, int v, int c){

    g[u].push_back({v,c,(int)g[v].size()});
    g[v].push_back({u,0,(int)g[u].size()-1});

}

bool bfs(){

    fill(lvl.begin(), lvl.end(), -1);
    lvl[S]=0; q=queue<int>(); q.push(S);

    while(!q.empty()){

        int u=q.front(); q.pop();
        for(auto &e: g[u]){
            if(lvl[e.v]<0 && e.c>0){
                lvl[e.v]=lvl[u]+1;
                q.push(e.v);
            }
        }
    }


    return lvl[T]>=0;
}

int dfs(int u, int f){

    if(!f||u==T) return f;

    for(int &i=ptr[u]; i<(int)g[u].size(); i++){

        E &e=g[u][i];
        if(lvl[e.v]==lvl[u]+1 && e.c>0){
            int w = dfs(e.v, min(f, e.c));
            if(w){
                e.c -= w;
                g[e.v][e.r].c += w;
                return w;
            }
        }
    }


    return 0;
}

int maxf(){
    int flow=0;

    while(bfs()){
        fill(ptr.begin(), ptr.end(), 0);
        while(int p = dfs(S, INF))
            flow += p;
    }

    return flow;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    while(cin >> n >> m){

        vector<int> C(n), P(m), B(m);

        for(int i=0;i<n;i++) cin>>C[i];
        for(int i=0;i<m;i++) cin>>P[i];

        vector<vector<int>> cat(m);
        for(int i=0;i<m;i++){

            cin>>B[i];
            cat[i].resize(P[i]);

            for(int &x: cat[i]){ cin>>x; --x; }
        }

        S = 0; T = m + n + 1;
        int N = T + 1;
        g.assign(N, {});
        lvl.assign(N, 0);
        ptr.assign(N, 0);
        long long totB = 0;

        for(int i=0;i<m;i++){

            add(S, 1+i, B[i]);
            totB += B[i];
        }

        for(int j=0;j<n;j++){
            add(1+m+j, T, C[j]);
        }

        for(int i=0;i<m;i++){

            for(int x: cat[i]){
                add(1+i, 1+m+x, INF);
            }

        }


        cout << (totB - maxf()) << "\n";
    }
    return 0;
}
