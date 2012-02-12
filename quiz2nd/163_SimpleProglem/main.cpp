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

struct SegmentTree {
  LL n;
  vector<pair<LL, LL> > data;

  SegmentTree(LL n_) {
    n = 1;
    while (n < n_) n <<= 1;
    data = vector<pair<LL, LL> >(n*4, pair<LL, LL>(0, 0));
  }

  void add_(LL begin, LL end, LL x, LL k, LL l, LL r) {
    if (begin <= l && r <= end) {
      data[k].second += x;
    } else {
      if (l < end && r > begin) {
        if (r - l >= 2) {
          data[k].first += (min(end, r) - max(begin, l)) * x;
          LL chl = k * 2 + 1;
          LL chr = k * 2 + 2;
          add_(begin, end, x, chl, l, (l+r)/2);
          add_(begin, end, x, chr, (l+r)/2, r);
        }
      }
    }
  }

  void add(LL begin, LL end, LL x) {
    add_(begin, end, x, 0, 0, n);
  }

  LL sum_(LL begin, LL end, LL k, LL l, LL r) {
    LL ans = 0;
    if (begin <= l && r <= end) {
      ans += data[k].second* (r-l) + data[k].first;
    } else {
      if (l < end && r > begin) {
        if (r - l >= 2) {
          ans += data[k].second * (min(end, r) - max(begin, l));
          LL chl = k * 2 + 1;
          LL chr = k * 2 + 2;
          ans += sum_(begin, end, chl, l, (l+r)/2);
          ans += sum_(begin, end, chr, (l+r)/2, r);
        }
      }
    }
    return ans;
  }

  LL sum(LL begin, LL end) {
    return sum_(begin, end, 0, 0, n);
  }
};


// 17880K	3079MS at POJ
int main() {
  LL N, Q; 
  scanf("%lld %lld", &N, &Q);
  vector<LL> A(N);
  REP(i, N) {
    LL a;
    scanf("%lld", &a);
    A[i] = a;
  }

  // initialize segment tree
  SegmentTree tree(A.size());
  REP(i, A.size()) {
    tree.add(i, i+1, A[i]);
  }

  // process requests
  REP(i, Q) {
    char q; cin >> q;
    if (q == 'Q') {
      LL l, r;
      scanf("%lld %lld", &l, &r);
      cout << tree.sum(l-1, r) << endl;
    } else {
      LL l, r, x;
      scanf("%lld %lld %lld", &l, &r, &x);
      tree.add(l-1, r, x);
    }
  }
}

