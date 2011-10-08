#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
#define dump(x)  cerr << #x << " = " << (x) << endl;

#define INF 100000

int solve(int n, vector<int>& w, vector<int>& v, int W) {
    // dp[i][j]: i番目までの品物から価値がjになるよう
    // 選んだ時の最小の重さ
    vector<vector<int> > dp(n, vector<int>(n*100+1, INF));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n * 100; j++) {
            if (i == 0) {
                if (j == v[i]) dp[i][j] = w[i];
            } else {
                if (j >= v[i]) {
                    dp[i][j] = min(dp[i-1][j], dp[i-1][j-v[i]] + w[i]);
                } else {
                    dp[i][j] = dp[i-1][j];
                }
            }
        }
    }

    int maxW = 0;
    for (int j = 0; j <= n * 100; j++) {
        if (dp[n-1][j] <= W) maxW = max(maxW, j);
    }

    return maxW;
}

int main() {
    int n; cin >> n;
    vector<int> w(n), v(n);
    REP(i, n) cin >> w[i] >> v[i];
    int W; cin >> W;

    int answer = solve(n, w, v, W);
    cout << "Answer: " << answer << endl;
}

