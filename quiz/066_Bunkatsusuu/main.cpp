#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
#define dump(x)  cerr << #x << " = " << (x) << endl;

int n = 4;
int m = 3;
int M = 10000;

int main() {
    vector<vector<int> > dp(n+1, vector<int>(m+1, 0));
    // dp[i][j]: iのj分割の全パターン数。
    //
    // j分割ちょうどになっているパターンの数は、
    // 分割された数から1ずつ引くことができるので、
    // i-jのj分割と数が同じ。
    //
    // j-1分割以下になっている数は、そのままiのj-1分割の数。
    // よって dp[i][j] = dp[i-j][j] + dp[i][j-1]
    // また、0の0分割は1とおける
    //
    dp[0][0] = 1;
    for (int i = 0; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (i >= j)
                dp[i][j] = dp[i-j][j] + dp[i][j-1];
            else
                dp[i][j] = dp[i][j-1];
        }
    }
    REP(i, n+1) {
        REP(j, m+1) cerr << dp[i][j] << " ";
        cerr << endl;
    }
    cout << dp[n][m] << endl;
}

