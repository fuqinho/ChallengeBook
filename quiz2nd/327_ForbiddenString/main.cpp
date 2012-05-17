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

const int MOD = 10009;
const string AGCT = "AGCT";

int n = 3;
int k = 2;
string S = "AT";

int main() {
  // next[i][j]: i番目のパターンの後に文字AGCT[j]を足すとどのパターンになるか
  VVI next(k, 4);
  REP(i, k) {
    REP(j, 4) {
      string snext = S.substr(0, i) + AGCT[j];
      while (S.substr(0, snext.size()) != snext) snext = snext.substr(1, snext.size()-1);
      if (snext.size() == S.size()) {
        next[i][j] = -1;
      } else {
        next[i][j] = snext.size();
      }
    }
  }

  VVI dp(n+1, VI(k, 0));
  dp[0][0] = 1;
  REP(i, n) {
    REP(j, k) {
      REP(l, 4) {
        if (next[j][l] != -1) {
          dp[i+1][next[j][l]] += dp[i][j];
          dp[i+1][next[j][l]] %= MOD;
        }
      }
    }
  }

  /*
  REP(j, k) {
    REP(i, n+1) cerr << dp[i][j] << " ";
    cerr << endl;
  }
  */

  int ans = 0;
  REP (i, k) ans += dp[n][i];
  cout << (ans % MOD) << endl;

  /*
  REP(i, k) {
    REP(j, 4) {
      cerr << next[i][j] << " ";
    }
    cerr << endl;
  }
  */
}

