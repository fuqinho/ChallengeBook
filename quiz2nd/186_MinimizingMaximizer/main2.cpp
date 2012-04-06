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
#include <climits>
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

static const int INF = 100000000;

class RMQ {
public:

  RMQ(int n_) {
    local_size = 1;
    while (local_size < n_) local_size *= 2;
    minimum = vector<int>(2 * local_size - 1);
    for (int i = 0; i < 2 * local_size - 1; i++) minimum[i] = INF;
  }

  // update element at k by a
  void update(int k, int a) {
    k += local_size - 1;
    minimum[k] = a;
    while (k > 0) {
      k = (k - 1) / 2;
      minimum[k] = min(minimum[k*2+1], minimum[k*2+2]);
    }
  }

  // get minimum element in [a, b)
  int query(int a, int b) {
    return query_(a, b, 0, 0, local_size);
  }

private:
  int local_size;
  vector<int> minimum;

  int query_(int a, int b, int k, int l, int r) {
    if (r <= a || b <= l) return INF;

    if (a <= l && b >= r) {
      return minimum[k];
    } else {
      int vl = query_(a, b, k*2+1, l, (l+r)/2);
      int vr = query_(a, b, k*2+2, (l+r)/2, r);
      return min(vl, vr);
    }
  }
};

int main() {
  int n, m;
  scanf("%d %d", &n, &m);

  vector<PII> sorters(m);
  REP(i, m) {
    scanf("%d %d", &sorters[i].first, &sorters[i].second);
  }
 
  // dp[i][j]: 
  VI dp(n+1, INF);
  RMQ rmq(n+1);

  //dp[1] = 0;
  rmq.update(0, 0);
  REP(i, m) {
    int s = sorters[i].first;
    int t = sorters[i].second;

    int minLength = rmq.query(s-1, t);
    //dp[t] = min(minLength + 1, dp[t]);
    int next = min(minLength + 1, rmq.query(t-1, t));
    rmq.update(t-1, next);
  }
  cout << rmq.query(n-1, n) << endl;
}

