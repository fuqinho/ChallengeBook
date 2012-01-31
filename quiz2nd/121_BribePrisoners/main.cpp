#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
#define dump(x)  cerr << #x << " = " << (x) << endl;

int solve(int P, vector<int>& a) {
    int Q = a.size();
    // dp[i,j] : 囚人A[i]と囚人A[j]の間にいる囚人を全員解放するのにかかるコイン
    vector<vector<int> >  dp(a.size()+1, vector<int>(a.size()+2, 0));
    vector<int> A;
    A.push_back(0);
    for (int i = 0; i < a.size(); i++) A.push_back(a[i]);
    A.push_back(P + 1);

    //for (int i = 0; i < A.size(); i++) cerr << A[i] << " "; cerr << endl;
    
    for (int w = 2; w <= Q + 1; w++) {
        /*
        cerr << "====== w: " << w << " ======" << endl;
        REP(x, Q+1) {
            REP(y,  Q+2) cerr << dp[x][y] << " ";
            cerr << endl;
        }
        */
        for (int i = 0; i + w <= Q + 1; i++) {
            // dp[i][j]を計算する
            int j = i + w;
            int t = numeric_limits<int>::max();
            for (int k = i + 1; k < j; k++) {
                t = min(t, dp[i][k] + dp[k][j]);
            }
            dp[i][j] = t + A[j] - A[i] - 2;
        }
    }

    return dp[0][Q + 1];
}

int main() {
    int P, Q;
    cin >> P >> Q;
    vector<int> A(Q);
    REP(i, Q) cin >> A[i];

    int ans = solve(P, A);
    dump(ans);
}

