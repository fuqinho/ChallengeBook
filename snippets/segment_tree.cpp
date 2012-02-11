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
#include <cmath>
#include <cstdio>
#include <climits>
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
#define checkn(x,n) cerr << #x << " = "; for(int i=0;i<(x).size()&&i<(n);++i) cerr << (x)[i] << " "; cerr << endl;

const int MAX_N = 1 << 17;
int n, dat[2 * MAX_N - 1];

void init(int n_) {
  // 要素数をべき乗にする
  n = 1;
  while (n < n_) n *= 2;
  
  for (int i = 0; i < 2 * n - 1; i++) dat[i] = INT_MAX;
}

// k番目の値をaに変更
void update(int k, int a) {
  // 葉の接点
  k += n - 1;
  dat[k] = a;
  // 登りながら更新
  while (k > 0) {
    k = (k - 1) / 2;
    dat[k] = min(dat[k * 2 + 1], dat[k * 2 + 2]);
  }
}

// [a, b)の最小値を求める
int query(int a, int b, int k, int l, int r) {
  if (r <= a || b <= l) return INT_MAX;
  if (a <= l && r <= b) return dat[k];
  else {
    int vl = query(a, b, k*2+1, l, (l+r)/2);
    int vr = query(a, b, k*2+2, (l+r)/2, r);
    return min(vl, vr);
  }
}

int main() {
  int temp[] = {2, 1, 6, 3, 7, 5, 4, 2};
  init(8);
  REP(i, 8) update(i, temp[i]);
  
  cout << query(0, 3, 0, 0, 8) << endl;
  cout << query(2, 6, 0, 0, 8) << endl;
}

