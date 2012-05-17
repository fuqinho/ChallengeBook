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

// 素因数分解
std::map<int, int> prime_factor(int n) {
  map<int, int> res;
  for (int i = 2; i * i <= n; i++) {
    while (n % i == 0) {
      ++res[i];
      n /= i;
    }
  }
  if (n != 1) res[n] = 1;
  return res;
}

// 約数の列挙
vector<int> divisor(int n) {
  vector<int> res;
  for (int i = 1; i * i <= n; i++) {
    if (n % i == 0) {
      res.push_back(i);
      if (i != n / i) res.push_back(n / i);
    }
  }
  return res;
}

// 合同式のべき乗: x^n (mod m)
LL mod_pow(LL x, LL n, LL m) {
  if (n == 0) return 1;
  LL res = mod_pow(x * x % m, n / 2, m);
  if (n & 1) res = res * x % m;
  return res;
}

int main() {
  int n, m; cin >> n >> m;

  map<int, int> primes = prime_factor(n);
  vector<int> divs = divisor(n);
  LL res = 0;

  const int MOD = 1000000007;

  REP(i, divs.size()) {

    // オイラー関数のdivs[i]での値を求める
    LL euler = divs[i];
    dump(divs[i]);
    for (map<int, int>::iterator it = primes.begin(); it != primes.end(); ++it) {
      int p = it->first;
      if (divs[i] % p == 0) euler = euler / p * (p-1);
    }

    dump(euler);

    res += euler * mod_pow(m, n / divs[i], MOD);
    res %= MOD;
  }

  printf("%lld\n", res * mod_pow(n, MOD-2, MOD) % MOD);


}

