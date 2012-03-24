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

int MOD = 10000;

VVI mult(VVI& m1, VVI& m2) {
  VVI res(2, VI(2, 0));
  REP(i, 2) {
    REP(j, 2) {
      res[i][j] = (m1[i][0] * m2[0][j] + m1[i][1] * m2[1][j]) % MOD;
    }
  }
  return res;
}

int main() {
  VVI curVec(2, VI(2,0));
  curVec[0][0] = curVec[0][1] = curVec[1][0] = 1;

  VVI res(2, VI(2,0));
  res[0][0] = res[1][1] = 1;

  //long long n = 1000000000000000;
  long long n = 10;
  while (n > 0) {

    REP(i, 2) {
      REP (j, 2) cout << curVec[i][j] << " ";
      cout << endl;
    }
    cout << endl;

    if (n & 1) {
      res = mult(res, curVec);
    }
    n >>= 1;
    curVec = mult(curVec, curVec);
  }
  
  cout << res[1][0] % MOD << endl;
}

