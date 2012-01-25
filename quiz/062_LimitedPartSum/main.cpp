#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
#define dump(x)  cerr << #x << " = " << (x) << endl;

int n = 3;
int a[] = {3, 5, 8};
int m[] = {3, 2, 2};
int K = 17;





// bool値を求めるDP。非効率
void solve0() {
    vector< vector<bool> > dp(n + 1, vector<bool>(K + 1, false));
    // dp[i+1][j]: i番目まででjが作れるか
    dp[0][0] = true;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= K; j++) {
            // i-1番目まででj, j-a[i], j-2*a[i],..., j-k*a[i]...が作れてないといけない
            for (int k = 0; k <= m[i] && j-k*a[i] >= 0; k++) {
                dp[i+1][j] = dp[i+1][j] || dp[i][j-k*a[i]];
            }
        }
    }

    REP(i, n+1) {
        REP(j, K+1) cout << dp[i][j] << " ";
        cout << endl;
    }
    cout << dp[n][K] << endl;
}

// 効率化
void solve1() {
    vector< vector<int> > dp(n + 1, vector<int>(K + 1, -1));
    // dp[i+1][j]: i番目まででjを作る場合のi番目の数の個数
    dp[0][0] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= K; j++) {
            if (dp[i][j] >= 0) {
                dp[i+1][j] = m[i];
            } else if (j-a[i] >= 0 && dp[i+1][j-a[i]] > 0) {
                dp[i+1][j] = dp[i+1][j-a[i]] - 1;
            }
        }
    }

    REP(i, n+1) {
        REP(j, K+1) cout << dp[i][j] << " ";
        cout << endl;
    }
    cout << dp[n][K] << endl;
}

// 配列の再利用
void solve2() {
    vector<int> dp(K + 1, -1);
    // dp[i+1][j]: i番目まででjを作る場合のi番目の数の個数
    dp[0] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= K; j++) {
            if (dp[j] >= 0) {
                dp[j] = m[i];
            } else if (j-a[i] >= 0 && dp[j-a[i]] > 0) {
                dp[j] = dp[j-a[i]] - 1;
            }
        }
    }

    REP(j, K+1) cout << dp[j] << " ";
    cout << endl;
    cout << dp[K] << endl;
}

int main() {
    solve0();
    solve1();
    solve2();
}

