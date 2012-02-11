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
#include <cstdio>
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
#define checkn(x,n) cerr << #x << " = "; for(int i=0;i<(x).size()&&i<(n);++i) cerr << (x)[i] << " "; cerr << endl;

int n = 4;
LL W = 5;
LL w[] = {2, 1, 3, 2};
LL v[] = {3, 2, 4, 2};

int main() {
  vector<PII> v1;
  for (int mask = 0; mask < (1 << (n / 2)); mask++) {
    LL v_sum = 0;
    LL w_sum = 0;
    for (int i = 0; i < n/2; i++) {
      if (mask & (1 << i)) {
        v_sum += v[i];
        w_sum += w[i];
      }
    }
    v1.push_back(PII(w_sum, v_sum));
  }
  sort(ALL(v1));
  //debug(v1.size());
  // いらない分は取り除く
  LL maxValue = -1;
  vector<PII> v2;
  REP(i, v1.size()) {
    if (v1[i].second > maxValue) {
      v2.push_back(v1[i]);
      maxValue = v1[i].second;
    }
  }
  /*
  debug(v2.size());
  REP(i, v2.size()) {
    cout << "(" << v2[i].first << ", " << v2[i].second << ")" << endl;
  }
  */

  LL res = 0;
  for (int mask = 0; mask < (1 << (n - n / 2)); mask++) {
    LL v_sum = 0;
    LL w_sum = 0;
    for (int i = 0; i < n - n / 2; i++) {
      if (mask & (1 << i)) {
        v_sum += v[i + n / 2];
        w_sum += w[i + n / 2];
      }
    }
    if (w_sum <= W) {
      LL tv = (lower_bound(v2.begin(), v2.end(), PII(W - w_sum, 1000)) - 1)->second;
      res = max(res, v_sum + tv);
    }
  }

  cout << res << endl;
}

