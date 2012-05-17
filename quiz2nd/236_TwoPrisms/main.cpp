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

static const int INF = 100000000;

double width(const vector<PII>& P, double x) {
  double lb = INF;
  double ub = -INF;

  REP(i, P.size()) {
    int i_next = (i + 1) % P.size();
    int x1 = P[i].first;
    int x2 = P[i_next].first;
    if ((x1 - x) * (x2 - x) <= 0) {
      int y1 = P[i].second;
      int y2 = P[i_next].second;
      double y = y1;
      if (x2 - x1 != 0) {
        y = (y1 * (x2 - x) + y2 * (x - x1)) / double(x2 - x1);
      }
      lb = min(lb, y);
      ub = max(ub, y); 
    }
  }

  return ub - lb;
}

double solve(int M, int N, const vector<PII>& P_XY, const vector<PII>& P_XZ) {
  int min1 = INF, min2 = INF, max1 = -INF, max2 = -INF;
  vector<int> xs;
  REP(i, M) {
    min1 = min(min1, P_XY[i].first);
    max1 = max(max1, P_XY[i].first);
    xs.push_back(P_XY[i].first);
  }
  REP(i, N) {
    min2 = min(min2, P_XZ[i].first);
    max2 = max(max2, P_XZ[i].first);
    xs.push_back(P_XZ[i].first);
  }

  sort(ALL(xs));
  xs.erase(unique(ALL(xs)), xs.end());

  double res = 0.0;

  for (int i = 0; i+1 < xs.size(); i++) {
    if (xs[i] >= min1 && xs[i] <= max1 && xs[i] >= min2 && xs[i] <= max2 &&
        xs[i+1] >= min1 && xs[i+1] <= max1 && xs[i+1] >= min2 && xs[i+1] <= max2) {
      double a = xs[i];
      double b = xs[i+1];
      double c = (a + b) / 2.0;
      double fa = width(P_XY, a) * width(P_XZ, a);
      double fb = width(P_XY, b) * width(P_XZ, b);
      double fc = width(P_XY, c) * width(P_XZ, c);

      res += (b - a) * (fa + fb + 4 * fc) / 6.0;
    }
  }

  return res;
}

int main() {
  while (true) {
    int M, N; scanf("%d %d", &M, &N);
    if (M == 0 && N == 0) break;

    vector<PII> P_XY(M);
    vector<PII> P_XZ(N);
    REP(i, M) scanf("%d %d", &P_XY[i].first, &P_XY[i].second);
    REP(i, N) scanf("%d %d", &P_XZ[i].first, &P_XZ[i].second);

    double ans = solve(M, N, P_XY, P_XZ);
    printf("%.10f\n", ans);
  }
}

