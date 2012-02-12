#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<string> VS;
typedef pair<int, int> PII;
typedef long long LL;
#define ALL(a)  (a).begin(),(a).end()
#define RALL(a) (a).rbegin(), (a).rend()
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
const double EPS = 1e-10;
const double PI  = acos(-1.0);
#define dump(x)  cerr << #x << " = " << (x) << endl;
#define debug(x) cerr << #x << " = " << (x) << " (L" << __LINE__ << ")" << " " << __FILE__ << endl;
#define check(x) cerr << #x << " = "; REP(q,(x).size()) cerr << (x)[q] << " "; cerr << endl;

template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& stream, const std::pair<T1, T2>& data) {
  return stream << "(" << data.first << "," << data.second << ")";
}

struct BinaryIndexedTree {
  BinaryIndexedTree(int n) {
    int size = 1;
    while (size < n) {
      size <<= 1;
    }
    v = vector<LL>(size + 1, 0);
  }
  LL sum(int i) {
    LL res = 0;
    while (i > 0) {
      res += v[i];
      i -= i & -i;
    }
    return res;
  }
  void add(int i, LL x) {
    while (i < v.size()) {
      v[i] += x;
      i += i & -i;
    }
  }
  vector<LL> v;
};

// 4524K	1860MS at POJ
int main() {
  LL N, Q; 
  scanf("%lld %lld", &N, &Q);
  vector<LL> A(N);
  REP(i, N) {
    LL a;
    scanf("%lld", &a);
    A[i] = a;
  }

  BinaryIndexedTree bit0(A.size());
  BinaryIndexedTree bit1(A.size());
  for (int i = 0; i < A.size(); i++) {
    bit0.add(i+1, A[i]);
  }

  REP(i, Q) {
    char q; cin >> q;
    if (q == 'Q') {
      LL l, r;
      scanf("%lld %lld", &l, &r);

      LL res = 0;
      res += bit0.sum(r) + bit1.sum(r) * r;
      res -= bit0.sum(l - 1) + bit1.sum(l - 1) * (l - 1);
      cout << res << endl;

    } else {
      LL l, r, x;
      scanf("%lld %lld %lld", &l, &r, &x);

      bit0.add(l, -x * (l-1));
      bit1.add(l, x);
      bit0.add(r + 1, x * r);
      bit1.add(r + 1, -x);
    }
  }
}

