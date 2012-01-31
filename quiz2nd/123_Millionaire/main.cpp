#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
#define dump(x)  cerr << #x << " = " << (x) << endl;


double solve(int M, double P, int X) {
    vector<vector<double> > dp(M + 1, vector<double>((1 << M) + 1, 0));

    int n = 1 << M;
    dp[M][n] = 1.0;

    for (int m = M; m > 0; m--) {
        for (int i = 0; i <= n; i++) {
            int jub = min(i, n - 1);
            double t = 0.0;
            for (int j = 0; j <= jub; j++) {
                double p = P * dp[m][i + j] + (1 - P) * dp[m][i - j];
                dp[m-1][i] = max(dp[m-1][i], p);
            }
        }
    }
    
    int i = (long long)X * n / 1000000;
    return dp[0][i];
}

int main() {
    double ans1 = solve(1, 0.5, 500000);
    printf("%.6f\n", ans1);
    double ans2 = solve(3, 0.75, 600000);
    printf("%.6f\n", ans2);
}

