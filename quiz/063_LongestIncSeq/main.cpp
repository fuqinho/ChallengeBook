#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
#define dump(x)  cerr << #x << " = " << (x) << endl;

int n = 5;
int a[] = {4, 2, 3, 1, 5};
const int INF = 10000;

void solve1() {
    // dp[i]: 長さがi+1であるような増加部分列における最終要素の最小値
    vector<int> dp(n+1, INF);
    for (int i = 0; i < n; i++) {
        *lower_bound(dp.begin(), dp.end(), a[i]) = a[i];
        REP(j, n) cout << dp[j] << " ";
        cout << endl;
    }
    cout << lower_bound(dp.begin(), dp.end(), INF) - dp.begin() << endl;
}

void solve0() {
    // dp[i]: 最後がa[i]であるような部分列の長さ
    // a[i]だけか、dp[0]~dp[i-1]で最長のものにa[i]を付け加えたもの
    vector<int> dp(n, 1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }
    REP(i, n) cout << dp[i] << " ";
    cout << endl;
}

int main() {
    solve0();
    solve1();
}

