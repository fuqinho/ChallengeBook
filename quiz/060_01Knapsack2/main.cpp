#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
#define dump(x)  cerr << #x << " = " << (x) << endl;

#define INF 100000

int solve(int n, vector<int>& w, vector<int>& v, int W) {
    // dp[i][j]: i番目までの品物から価値がj以上になるよう
    // 選んだ時の最小の重さ
    vector<vector<int> > dp(n, vector<int>(n*100+1, INF));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n * 100; i++) {
            if (i == 0) {
                dp[i][j] = 
            }
        }
    }

    return 0;
}

int main() {
    int n; cin >> n;
    vector<int> w(n), v(n);
    REP(i, n) cin >> w[i] >> v[i];
    int W; cin >> W;

    int answer = solve(n, w, v, W);
    cout << "Answer: " << answer << endl;
}

