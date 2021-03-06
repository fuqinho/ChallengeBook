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

int main() {
  int n, m;
  scanf("%d %d", &n, &m);

  vector<PII> sorters(m);
  REP(i, m) {
    scanf("%d %d", &sorters[i].first, &sorters[i].second);
  }
 
  // dp[i][j]: 
  // i番目のSorterまでで、最大値がj番目に移動するような最小の部分列の長さ
  static const int INF = 100000000;
  VI dp(n+1, INF);

  dp[1] = 0;
  REP(i, m) {
    int s = sorters[i].first;
    int t = sorters[i].second;

    //cerr << "s: " << s << ", " << "t: " << t << endl;
    
    int minLength = INF;
    for (int j = s; j <= t; j++) {
      minLength = min(minLength, dp[j]);
    }
    dp[t] = min(minLength + 1, dp[t]);

  }
  cout << dp[n] << endl;

}

