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
#include <cmath>
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

struct BinaryIndexedTree {
  BinaryIndexedTree(int n) {
    int size = 1;
    while (size < n) {
      size <<= 1;
    }
    v = vector<int>(size + 1, 0);
  }
  int sum(int i) {
    int res = 0;
    while (i > 0) {
      res += v[i];
      i -= i & -i;
    }
    return res;
  }
  void add(int i, int x) {
    while (i < v.size()) {
      v[i] += x;
      i += i & -i;
    }
  }
  vector<int> v;
};

int main() {
  int n; cin >> n;
  vector<int> a(n);
  REP(i, n) cin >> a[i];

  BinaryIndexedTree bit(a.size());
  int answer = 0;
  for (int i = 0; i < a.size(); i++) {
    answer += i - bit.sum(a[i]);
    bit.add(a[i], 1);
  }
  dump(answer);
}

