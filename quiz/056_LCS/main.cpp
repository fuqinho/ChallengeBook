#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
#define dump(x)  cerr << #x << " = " << (x) << endl;

int solve(int N, int M, string S, string T) {

    // dp[i][j]: Sのi文字目とTのj文字目までの最長部分文字列長
    vector<vector<int> > dp(N+1, vector<int>(M+1, 0));

    REP(i, N) {
        REP(j, M) {
            if (S[i] == T[j]) {
                dp[i+1][j+1] = dp[i][j] + 1;
            } else {
                dp[i+1][j+1] = max(dp[i+1][j], dp[i][j+1]);
            }
        }
    }

    // print DP table
    REP(i, N+1) {
        REP(j, M+1) {
            cerr << dp[i][j] << " ";
        }
        cerr << endl;
    }

    return dp[N][M];
}

int main() {
    int N, M;
    string S, T;
    cin >> N >> M >> S >> T;

    int answer = solve(N, M, S, T);
    cout << "Answer: " << answer << endl;
}

