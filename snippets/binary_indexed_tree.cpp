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
    v = vector<int>(n + 1, 0);
  }
  // return sum of [0, i]
  int sum(int i) {
    i++;
    int s = 0;
    while (i > 0) {
      s += v[i];
      i -= i & -i;
    }
    return s;
  }

  // add x at index i
  void add(int i, int x) {
    i++;
    while (i <= v.size()) {
      v[i] += x;
      i += i & -i;
    }
  }

  vector<int> v;
};

int main() {
  BinaryIndexedTree bit(8);
  for (int i = 0; i < 8; i++) {
    bit.add(i, i+1);
  }
  check(bit.v);
  dump(bit.sum(3));
  dump(bit.sum(5));

}

