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

int main() {
  int n; cin >> n;
  vector<PII> a(n);
  REP(i, n) {
    int score; cin >> score;
    a[i] = PII(score, i);
  }
  sort(RALL(a));
  REP(i, a.size()) cerr << "(" << a[i].first << "," << a[i].second << ")" << endl;
  vector<int> teamA;
  vector<int> teamB;
  LL sumA = 0;
  LL sumB = 0;
  /*
  REP(i, a.size()) {
    if (
  }
  */


}

