#include <iostream>
#include <vector>
#include <string>


using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define INF 0x3f3f3f3f


int T, P;
int EP = 20;

struct Team {
    int id;
    int solved;
    int tp;
    int fa;
    int penalty = tp + EP*fa;
    Team(int i, int s, int tp, int fa) : id(i), solved(s), tp(tp), fa(fa) {};
};

struct Compare {
    bool operator()(Team a, Team b) {
        int penaltya = a.tp + EP * a.fa;
        int penaltyb = b.tp + EP * b.fa;
        bool c1 = a.solved > b.solved, c2 = penaltya < penaltyb, c3 = a.id < b.id;
        return a.solved != b.solved ? c1 : penaltya != penaltyb ? c2 : c3;
    }
};

vector<Team> teams;

void solve() {
    for (int t=0; t < T; ++t) {
        int solved=0, fa=0, tp=0, penalty=0; string s;
        for (int p=0; p < P; ++p)  {
            cin >> s; int idx = s.find('/');
            if (s.substr(idx+1) != "-") {
                fa += stoi(s.substr(0, idx)) - 1;
                tp += stoi(s.substr(idx+1));
                ++solved;
            }
        }
        teams.push_back(Team(t, solved, tp, fa));
    }
    sort(teams.begin(), teams.end(), Compare());

    int low = 1, high = INF;
    for (int i=0; i < teams.size()-1; ++i) {
        Team t1 = teams[i], t2 = teams[i+1];
        if (t1.solved != t2.solved || t1.fa == t2.fa) continue;
        if (t1.penalty == t2.penalty && t1.fa != t2.fa) {low = EP; high = EP; break;}

        if (t1.penalty < t2.penalty) {
            int tp_diff = t1.tp - t2.tp;
            int fa_diff = t1.fa - t2.fa;

            if (fa_diff == 0 || (fa_diff <= 0 && tp_diff <= 0)) continue; // EP pode ser qualquer valor

            int ep_ = (abs(tp_diff) + abs(fa_diff) - 1) / abs(fa_diff); // ceil(tp_diff / fa_diff)

            if (fa_diff > 0 && tp_diff < 0) high = min(ep_-1, high);
            
            if (fa_diff < 0 && tp_diff > 0) {
                if (tp_diff % abs(fa_diff) == 0) low = max(ep_+1, low);
                else low = max(ep_, low);
            }
        }        
    }
    
    cout << low << " ";
    if (high == INF) cout << '*' << endl;
    else cout << high << endl;
    teams.clear();
}


int main(void) {_
    while(cin >> T >> P && !(T == 0 && P == 0)) {solve();}

   exit(0);
}