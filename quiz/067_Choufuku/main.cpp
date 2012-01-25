#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
#define dump(x)  cerr << #x << " = " << (x) << endl;

int n = 3;
int m = 3;
int a[] = {1, 2, 3};
int M = 10000;

int main() {
    vector<vector<int> > dp(n+1, vector<int>(m+1, 0));
    
    // 1つも選ばない方法は常に1通り
    for (int i = 0; i <= n; i++) dp[i][0] = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= m; j++) {
            /*
            for (int k = 0; k <= a[i] && j - k >= 0; k++) {
                dp[i+1][j] += dp[i][j-k];
            }
            */
            if (j - a[i] - 1 >= 0) {
                dp[i+1][j] = dp[i+1][j-1] + dp[i][j] - dp[i][j-a[i]-1];
            } else {
                dp[i+1][j] = dp[i+1][j-1] + dp[i][j];
            }
        }
    }
    cout << dp[n][m] << endl;
}

