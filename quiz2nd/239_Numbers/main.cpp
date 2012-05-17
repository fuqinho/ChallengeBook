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

static const int MOD = 1000;

VVI mul(const VVI& a, const VVI& b) {
  int size = a.size();
  VVI res(size, VI(size, 0));
  REP(i, size) {
    REP(j, size) {
      REP(k, size) {
        res[i][j] += a[i][k] * b[k][j]; 
        res[i][j] %= MOD;
      }
    }
  }
  return res;
}

VVI pow(VVI A, int n) {
  int size = A.size();
  VVI ans(size, VI(size, 0));
  REP(i, size) ans[i][i] = 1;
 
  VVI tmp(size, VI(size, 0));
  REP(i, size) tmp[i][i] = 1;
  while (n > 0) {
    if (n & 1) {
      ans = mul(ans, A);
    }
    A = mul(A, A);
    n >>= 1;
  }
  return ans;
}

void solve(int t, int n) {
  VVI A(2, VI(2));
  A[0][0] = 3; A[0][1] = 5;
  A[1][0] = 1; A[1][1] = 3;

  VVI AN = pow(A, n);

  printf("Case #%d: %03d\n", t, (AN[0][0] * 2 - 1) % MOD);
}

int main() {
  int T; cin >> T;
  for (int i = 1; i <= T; i++) {
    int n; cin >> n;
    solve(i, n);
  }
}

