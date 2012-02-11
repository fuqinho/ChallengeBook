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

int n = 3;
int k = 2;
int w[] = {2, 5, 2};
int v[] = {2, 3, 1};

bool C(vector<PII>& items, double x, int K) {
  vector<double> temp(items.size());
  REP(i, items.size()) {
    temp[i] = items[i].second - x * items[i].first;
  }
  int c = 0;
  double sum = 0;
  REP(i, temp.size()) {
    sum += temp[i];
    if (sum >= 0.0) c++;
  }
  return c >= K;
}

double solve(vector<PII>& items, int k) {
  double lb = 0.0;
  double ub = 10000.0;
  REP(i, 100) {
    double mid = (lb + ub) / 2;
    if (C(items, mid, k)) {
      lb = mid;
    } else {
      ub = mid;
    }
  }
  return lb;
}

int main() {
  vector<PII> items(n);
  REP(i, n) items[i] = PII(w[i], v[i]);
  double answer = solve(items, k);
  debug(answer);
}

