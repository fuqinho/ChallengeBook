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
  int x, k; cin >> x >> k;
  VI a(k);
  REP(i, k) cin >> a[i];

  // dp[i] = true : 残りi枚の状態で自分の番なら勝てる
  VI dp(x+1, 0);
  dp[0] = -1;
  for (int i = 1; i <= x; i++) {
    REP(j, k) {
      int nextCoin = i - a[j];
      if (nextCoin >= 0) {
        if (dp[nextCoin] == -1) {
          dp[i] = 1;
          break;
        }
      }
      dp[i] = -1;
    }
  }

  dumpv(dp);

  if (dp[x] == 1) {
    cout << "Alice" << endl;
  } else {
    cout << "Bob" << endl;
  }


}

