#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
#define dump(x)  cerr << #x << " = " << (x) << endl;

int solve(int n, vector<int>& w, vector<int>& v, int W) {
    vector<vector<int> > maxValue(n, vector<int>(W+1, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= W; j++) {
            if (i == 0) {
                if (j >= w[i]) {
                    maxValue[i][j] = maxValue[i][j-w[i]] + v[i];
                }
            } else {
                if (j >= w[i]) {
                    maxValue[i][j] = max(maxValue[i-1][j], maxValue[i][j-w[i]] + v[i]);
                } else {
                    maxValue[i][j] = maxValue[i-1][j];
                }
            }
        }
    }

    // print dp table
    REP(i, n) {
        REP(j, W+1) cout << maxValue[i][j] << " ";
        cout << endl;
    }

    return maxValue[n-1][W];
}

int main() {
    int n; cin >> n;
    vector<int> w(n), v(n);
    REP(i, n) cin >> w[i] >> v[i];
    int W; cin >> W;
    
    int answer = solve(n, w, v, W);
    cout << "Answer: " << answer << endl;
}

