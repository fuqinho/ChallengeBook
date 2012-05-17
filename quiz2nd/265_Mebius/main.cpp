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

map<int, int> moebius(int n) {
  map<int, int> res;
  vector<int> primes;

  // nの素因数を列挙する
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      primes.push_back(i);
      while (n % i == 0) n /= i;
    }
  }
  if (n != 1) primes.push_back(n);

  int m = primes.size();
  for (int i = 0; i < (1 << m); i++) {
    int mu = 1;
    int d = 1;
    for (int j = 0; j < m; j++) {
      if (i >> j & 1) {
        mu *= -1;
        d *= primes[j];
      }
    }
    res[d] = mu;
  }
  return res;
}


LL mod_pow(LL x, LL n, LL mod) {
  if (n == 0) return 1;
  LL res = mod_pow(x * x % mod, n / 2, mod);
  if (n & 1) res = res * x % mod;
  return res;
}

int main() {
  int n; cin >> n;

  const int MOD = 10009;

  int res = 0;
  map<int, int> mu = moebius(n);
  for (map<int, int>::iterator it = mu.begin(); it != mu.end(); ++it) {
    res += it->second * mod_pow(26, n / it->first, MOD);
    res = (res % MOD + MOD) % MOD;
  }
  cout << res << endl;
}

