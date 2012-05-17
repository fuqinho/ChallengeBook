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
#include <cstring>
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


LL merge_count(VI& a) {
  int n = a.size();
  if (n <= 1) return 0;

  LL cnt = 0;
  VI b(a.begin(), a.begin() + n/2);
  VI c(a.begin() + n/2, a.end());

  cnt += merge_count(b);
  cnt += merge_count(c);

  // cに含まれる各数字について、Bに
  int ai = 0, bi = 0, ci = 0;
  while (ai < n) {
    if (bi < b.size() && (ci == c.size() || b[bi] <= c[ci])) {
      a[ai] = b[bi];
      ai++;
      bi++;
    }
    // 部分列Cの最小値の方がBの最小値より小さい場合は、
    // 今現在Bに残っている数字は全て今注目しているCの最小値より大きい事になるので、
    // それらをカウントする
    else {
      cnt += n / 2 - bi; // 部分列Bに残っている数字の数を足す
      a[ai] = c[ci];
      ai++;
      ci++;
    }
  }
  return cnt;
}

int main() {
  int n = 4;
  int a[] = {3, 1, 4, 2};
  VI A(n);
  REP(i, n) A[i] = a[i];

  int ans = merge_count(A);
  cout << ans << endl;
}

