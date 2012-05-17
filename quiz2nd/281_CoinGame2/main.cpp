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


int main() {
  int n, k; cin >> n >> k;
  vector<int> a(k), x(n);
  REP(i, k) cin >> a[i];
  REP(i, n) cin >> x[i];

  vector<int> grundy(10001, 0);
  for (int i = 1; i <= 10000; i++) {
    set<int> s;
    for (int j = 0; j < k; j++) {
      if (i - a[j] >= 0) s.insert(grundy[i-a[j]]);
    }
    int next_grundy = 0;
    while (s.find(next_grundy) != s.end()) {
      next_grundy++;
    }
    grundy[i] = next_grundy;
  }

  int nim = 0;
  REP(i, n) nim ^= grundy[x[i]];

  if (nim != 0) {
    cout << "Alice" << endl;
  } else {
    cout << "Bob" << endl;
  }
}

