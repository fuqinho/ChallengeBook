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

void print(int n) {
  vector<int> v(10);;
  int idx = 0;
  while (n > 0) {
    v[idx] = (n & 1);
    idx++;
    n >>= 1;
  }
  reverse(ALL(v));
  REP(i, v.size()) cerr << v[i];
  cerr << endl;
}

int main() {
  int n; cin >> n;
  VI a(n);
  REP(i, n) cin >> a[i];

  REP(i, n) {
    print(a[i]);
  }
  cerr << "-----------------" << endl;
  int xor_res = 0;
  REP(i, n) xor_res ^= a[i];
  print(xor_res);

  if (xor_res != 0) {
    cout << "Alice" << endl;
  } else {
    cout << "Bob" << endl;
  }
}

