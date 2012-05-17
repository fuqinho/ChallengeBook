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

typedef vector<double> vec;
typedef vector<vec> mat;

// Ax = bを解く
vec gauss_jordan(const mat& A, const vec& b) {
  
  // 行列Aの後ろにbを並べた行列Bを作る
  int n = A.size();
  mat B(n, vec(n+1));
  REP(i, n) REP(j, n) B[i][j] = A[i][j];
  REP(i, n) B[i][n] = b[i];

  REP(i, n) {
    // 注目している変数の係数の絶対値が最も大きい式をi番目に持ってくる
    int pivot = i;
    for (int j = i; j < n; j++) {
      if (abs(B[j][i]) > abs(B[pivot][i])) pivot = j;
    }
    swap(B[i], B[pivot]);

    // B[i][i]の絶対値が0なら、注目している変数の係数が全て0なので解なし
    if (abs(B[i][i]) < EPS) return vec();

    // 注目している変数の係数を1にする
    for (int j = i+1; j <= n; j++) B[i][j] /= B[i][i];
    B[i][i] = 1; // not necessary

    // 他の式から注目している変数の係数を消去
    REP(j, n) {
      if (i != j) {
        // j番目の式からi番目の変数を消去
        for (int k = i+1; k <= n; k++) {
          B[j][k] -= B[j][i] * B[i][k];
        }
        B[j][i] = 0; // not necessary
      }
    }
  }

  REP(i, n) {
    REP(j, n+1) cerr << B[i][j] << " ";
    cerr << endl;
  }

  // Bは、
  // 1x        = a
  //    1y     = b
  //       1z  = c
  // の形になってる
  vec res(n);
  REP(i, n) res[i] = B[i][n];

  return res;
}

int main() {

  //  x - 2y + 3z = 6
  // 4x - 5y + 6z = 12
  // 7x - 8y +10z = 21
  // を解く

  mat A(3, vec(3));
  A[0][0] = 1; A[0][1] = -2; A[0][2] = 3;
  A[1][0] = 4; A[1][1] = -5; A[1][2] = 6;
  A[2][0] = 7; A[2][1] = -8; A[2][2] = 10;

  vec b(3);
  b[0] = 6;
  b[1] = 12;
  b[2] = 21;

  vec ans = gauss_jordan(A, b);

  REP(i, ans.size()) cerr << ans[i] << endl;
}

