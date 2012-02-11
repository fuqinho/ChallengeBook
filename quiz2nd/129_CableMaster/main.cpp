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

int N = 4;
int K = 11;
double L[] = {8.02, 7.43, 4.57, 5.39};

int main() {
  vector<double> ropes(N);
  REP(i, N) ropes[i] = L[i];

  double min_length = 0.0;
  double max_length = *max_element(ALL(ropes));
  REP(i, 100) {
    double mid = (min_length + max_length) / 2;
    int res = 0;
    REP(j, ropes.size()) {
      res += static_cast<int>(floor(ropes[j] / mid));
    }
    if (res >= K) {
      min_length = mid;
    } else {
      max_length = mid;
    }
  }
  debug(min_length);
  debug(max_length);
}

