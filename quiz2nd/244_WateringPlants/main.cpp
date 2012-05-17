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


int N;
vector<int> X(N), Y(N), R(N);


LL inner(double x, double y, double r) {
  /*
  LL res = 0;
  REP(i, N) {
    double oo = sqrt((X[i]-x) * (X[i]-x) + (Y[i]-y) * (Y[i]-y));
    if (oo + R[i] < r) res |= (1 << i);
  }
  return res;
  */
  LL S = 0;
  REP(i, N) {
    if (R[i] <= r) {
      double dx = x - X[i], dy = y - Y[i], dr = r - R[i];
      if (dx * dx + dy *  dy <= dr * dr) {
        S  |= 1LL << i;
      }
    }
  }
  return S;
}

vector<pair<double, double> > intersection(int a, int b, double r) {
  vector<pair<double, double> > res;
  if (R[a] > r || R[b] > r) return res;

  double r1 = r - R[a];
  double r2 = r - R[b];
  if (Y[a] == Y[b]) {
    
  } else {
    double A = -double(X[b] - X[a]) / (Y[b] - Y[a]);
    double B = double((r1*r1 - r2*r2) - (X[a]*X[a]-X[b]*X[b])) / 2.0 * (Y[b]-Y[a]);
    double alpha = A * A + 1;
    double beta2 = -X[a] + A*B - A*Y[a];
    double gamma = X[a]*X[a] + B*B + Y[a]*Y[a] - 2*B*Y[a] - r1*r1;
    double d2 = beta2*beta2 - alpha*gamma;
    if (d2 > 0) {
      double d = sqrt(d2);
      double x1 = (-beta2 + d)/alpha;
      double y1 = A * x1 + B;
      double x2 = (-beta2 - d)/alpha;
      double y2 = A * x2 + B;
      res.push_back(make_pair(x1, y1));
      res.push_back(make_pair(x2, y2));
    }
  }
  return res;
}

// 半径rの2つの円で全て囲えるならtrueを返す
bool C(double r) {
  vector<LL> candidate;
  candidate.push_back(0LL);

  // どれかの円を中心にした円で囲う
  REP(i, N) {
    if (R[i] <= r)
      candidate.push_back(inner(X[i], Y[i], r) | 1LL << i);
  }

  // ２つの円に接した円で囲う
  REP(i, N) {
    REP(j, i) {
      /*
      vector<pair<double, double> > pos = intersection(i, j, r);
      REP(k, pos.size()) {
        candidate.push_back(inner(pos[k].first, pos[k].second, r));
      }
      */
      if (R[i] < r && R[j] < r) {
        double x1 = X[i], y1 = Y[i], r1 = r - R[i];
        double x2 = X[j], y2 = Y[j], r2 = r - R[j];
        double dx = x2 - x1;
        double dy = y2 - y1;
        double a = dx*dx + dy*dy;
        double b = ((r1*r1 - r2*r2)/a + 1) / 2;
        double d = r1*r1/a - b*b;
        if (d >= 0) {
          d = sqrt(d);
          double x3 = x1 + dx*b;
          double y3 = y1 + dy*b;
          double x4 = -dy * d;
          double y4 = dx * d;
          LL ij = 1LL << i | 1LL << j;
          candidate.push_back(inner(x3-x4, y3-y4, r) | ij);
          candidate.push_back(inner(x3+x4, y3+y4, r) | ij);
        }
      }
    }
  }

  // ２つの円をピックアップして、それが全部を囲ってるか調べる
  REP(i, candidate.size()) {
    REP(j, i) {
      if ((candidate[i] | candidate[j]) == (1LL << N) - 1) {
        return true;
      }
    }
  }
  return false;
}

double solve() {
  double lb = 0;
  double ub = 10000;
  for (int i = 0; i < 100; i++) {
    double mid = (lb + ub) / 2;
    if (C(mid)) ub = mid;
    else lb = mid;
  }
  return ub;
}

int main() {
  int T; cin >> T;
  REP(t, T) {
    cin >> N;
    X = VI(N); Y = VI(N); R = VI(N);
    REP(i, N) cin >> X[i] >> Y[i] >> R[i];

    double ans = solve();
    cout << "Case #" << (t+1) << ": " << ans << endl;
  }
}

