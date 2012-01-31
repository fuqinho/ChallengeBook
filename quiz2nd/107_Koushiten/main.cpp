#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
#define dump(x)  cerr << #x << " = " << (x) << endl;

pair<int, int> P1(1, 11);
pair<int, int> P2(5, 3);

int gcd(int m, int n) {
    if (n == 0) return m;
    else return gcd(n, m % n);
}

int main() {
    int m = abs(P1.first - P2.first);
    int n = abs(P1.second - P2.second);
    if (m < n) swap(m, n);
    cout << gcd(m, n) - 1 << endl;
}

