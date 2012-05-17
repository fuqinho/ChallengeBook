#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<string> VS;
typedef pair<int, int> PII;
typedef long long LL;
#define ALL(a)  (a).begin(),(a).end()
#define REP(i,n) for(int i=0;i<(n);++i)
const double EPS = 1e-10;
const double PI  = acos(-1.0);
#define dump(x) cerr << "  (L" << __LINE__ << ") " << #x << " = " << (x) << endl;
#define dumpv(x) cerr << "  (L" << __LINE__ << ") " << #x << " = "; REP(q,(x).size()) cerr << (x)[q] << " "; cerr << endl;
template<typename T1, typename T2>
ostream& operator<<(ostream& s, const pair<T1, T2>& d) {return s << "(" << d.first << "," << d.second << ")";}

int gcd(int a, int b) {
  if (b == 0) return a;
  else return gcd(b, a % b);
}

int main() {
  int n, m; cin >> n >> m;
  vector<int> a(m);
  REP(i, m) cin >> a[i];

  LL res = 0;
  for (int i = 1; i < (1 << m); i++) {
    dump(i);
    // iの立っているビットの個数を求める
    int num = 0;
    for (int j = i; j != 0; j >>= 1) num += j & 1;

    LL lcm = 1;
    for (int j = 0; j < m; j++) {
      if (i >> j & 1) {
        lcm = lcm / gcd(lcm, a[j]) * a[j];
        if (lcm > n) break;
      }
    }
    if (num % 2 == 0) res -= n / lcm;
    else res += n / lcm;
  }
  cout << res << endl;
}

