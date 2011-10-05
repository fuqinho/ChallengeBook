#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
#define dump(x)  cerr << #x << " = " << (x) << endl;

int solve(int N, vector<int>& v, vector<int>& w, int W) {
    // dp[i][j]: i番目までの品物から合計j以下の重さになるように
    // 選んだ時の価値の最大値
    vector<vector<int> > dp(N+1, vector<int>(W+1, 0));

    for (int i = 0; i < N; i++)
        for (int j = 0; j <= W; j++)
            if (j < w[i])
                dp[i+1][j] = dp[i][j];
            else
                dp[i+1][j] = max(dp[i][j], dp[i][j-w[i]] + v[i]);

    return dp[N-1][W];
}

int main() {
    int N; cin >> N;
    vector<int> v(N), w(N);
    REP(i, N) cin >> w[i] >> v[i];
    int W; cin >> W;

    int answer = solve(N, v, w, W);
    cout << "Answer: " << answer << endl;
}

