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

VVI mul(VVI& m1, VVI& m2) {
  VVI res(m1.size(), VI(m2.size(), 0));
  REP(i, m1.size()) {
    REP(j, m2[i].size()) {
      REP(k, m1[i].size()) {
        res[i][j] += m1[i][k] * m2[k][j];
      }
    }
  }
  return res;
}

int main() {
  int n = 4;
  int K = 2;

  VVI edges(n, VI(n, 0));
  edges[0][1] = 1;
  edges[1][2] = 1;
  edges[2][3] = 1;
  edges[3][0] = 1;
  edges[0][2] = 1;

  VVI matrix(n, VI(n, 0));
  REP(i, n) REP(j, n) if (edges[i][j] == 1) matrix[j][i] = 1;

  VVI ans(n, VI(n, 0));
  REP(i, n) ans[i][i] = 1;

  int k = K;
  while (k > 0) {
    if (k & 1) {
      ans = mul(ans, matrix);
    }
    matrix = mul(matrix, matrix);
    k >>= 1;
  }

  int path_num = 0;
  REP(i, n) REP(j, n) path_num += ans[i][j];
  cout << path_num << endl;
}

