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

typedef pair<double, double> P;

const double INF = 10000;
int N;
vector<P> A;

bool compare_y(const P& a, const P& b) {
  return a.second < b.second;
}

// Aの[st, en)区間についての最小２点間距離を求める
double dfs(int st, int en) {
  if (en - st <= 1) return INF;

  // 左右に分割するための基準xを保持しておく
  double x = A[(st+en)/2].first;

  // 左右に分割されたそれぞれでの最小２点間距離を求める
  double d1 = dfs(st, (st+en)/2);
  double d2 = dfs((st+en)/2, en);
  double d = min(d1, d2);

  // [st, en)区間を(st+en)/2を軸にinplace_mergeする。
  // その際、y座標で比較して、結果の部分列がy座標の昇順で並ぶようにする
  inplace_merge(A.begin()+st, A.begin()+(st+en)/2, A.begin()+en, compare_y);

  // 分割線の周囲(距離d以内)にある２点間距離を求める
  vector<int> b;
  for (int i = st; i < en; i++) {
    if (fabs(A[i].first - x) < d) {
      for (int j = b.size()-1; j >= 0; j--) {
        double dx = A[i].first - A[b[j]].first;
        double dy = A[i].second - A[b[j]].second;
        if (dy >= d) break;
        d = min(d, sqrt(dx*dx + dy*dy));
      }
      b.push_back(i);
    }
  }

  return d;
}

void solve() {
  sort(A.begin(), A.end());
  double d = dfs(0, N);

  if (d >= INF) {
    printf("INFINITY\n");
  } else {
    printf("%.4f\n", d);
  }
}

int main() {
  while (true) {
    scanf("%d", &N);
    if (N == 0) return 0;
    A = vector<P>(N);
    REP(i, N) {
      scanf("%lf %lf", &A[i].first, &A[i].second);
    }

    solve();
  }

}

