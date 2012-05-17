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


// ユークリッドの互除法
// a, b (a > b)の最大公約数を返す
int gcd(int a, int b) {
  if (b == 0) return a;
  else return gcd(b, a % b);
}

// 拡張ユークリッドの互除法
// a, b (a > b)の最大公約数を求めると同時に、
// ax + by = gcdの解x, yを一組求める
int extgcd(int a, int b, int& x, int& y)
{
  if (b == 0)
  {
    x = 1; y = 0;
    //cerr << a << "x + " << b << "y = " << a << endl;
    //cerr << "  (x = " << x << ", y = " << y << ")" << endl;
    return a;
  }
  else
  {
    int d = extgcd(b, a%b, x, y);
    int px = x;
    int py = y;
    x = py;
    y = px - (a / b) * py;
    //cerr << a << "x + " << b << "y = " << d << endl;
    //cerr << "  (x = " << x << ", y = " << y << ")" << endl;
    return d;
  }
}

// 逆元を求める
int mod_inverse(int a, int m) {
  int x, y;
  extgcd(a, m, x, y);
  dump(x);
  return (x + m) % m;
}

// オイラー関数の値を求める。O(√n)
int euler_phi(int n) {
  int res = n;
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      res = res / i * (i - 1);
      for (; n % i ==0; n /= i);
    }
  }
  if (n != 1) res = res / n * (n - 1);
  return res;
}

// オイラー関数の値のテーブルを作成 O(MAX_N)程度
vector<int> euler_phi2(int MAX_N) {
  vector<int> res(MAX_N);
  for (int i = 0; i < MAX_N; i++) res[i] = i;
  for (int i = 2; i < MAX_N; i++) {
    if (res[i] == i) {
      for (int j = i; j < MAX_N; j+=i) res[j] = res[j] / i * (i-1);
    }
  }
  return res;
}

// 連立線形合同式を解く
// (b, m)のペアを返す
pair<int, int> linear_congruence(const vector<int>& A,
    const vector<int>& B, const vector<int>& M) {

  // 最初は条件が無いので全ての整数を意味するx≡0 (mod1)としておく
  int x = 0;
  int m = 1;

  REP(i, A.size()) {
    int a = A[i] * m;
    int b = B[i] - A[i] * x;
    int d = gcd(M[i], a);
    if (b % d != 0) return make_pair(0, -1); // 解なし
    int t = b / d * mod_inverse(a/d, M[i]/d) % (M[i]/d);
    x = x + m * t;
    m *= M[i]/d;
  }
  return make_pair(x%m, m);
}



int main() {
  int x, y;

  /*
  int gcd = extgcd(12, 8, x, y);
  dump(gcd);
  dump(x);
  dump(y);
  */
  int res = mod_inverse(3, 7);
  dump(res);
  
  int euler1 = euler_phi(100);
  dump(euler1);

}

