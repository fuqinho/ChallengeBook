#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
#define dump(x)  cerr << #x << " = " << (x) << endl;

long long solve(vector<int>& x, vector<int>& y) {
    sort(x.begin(), x.end());
    sort(y.rbegin(), y.rend());
    long long res = 0;
    for (int i = 0; i < x.size(); i++) res += (long long)x[i] * y[i];
    return res;
}

int main() {
    int n; cin >> n;
    vector<int> vx, vy;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        vx.push_back(x);
    }
    for (int i = 0; i < n; i++) {
        int y; cin >> y;
        vy.push_back(y);
    }
    dump(solve(vx, vy));
}

