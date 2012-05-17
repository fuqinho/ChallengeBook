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

VI solve(int n, int k, VI& a) {
  VI ans;
  deque<int> dq;
  REP(i, k) {
    while (!dq.empty() && a[dq.back()] > a[i]) dq.pop_back();
    dq.push_back(i);
  }
  REP(i, n-k+1) {
    ans.push_back(a[dq.front()]);
    if (dq.front() == i) dq.pop_front();

    int next = i + k;
    while (!dq.empty() && a[dq.back()] > a[next]) dq.pop_back();
    dq.push_back(next);
  }

  return ans;
}

int main() {
  int n, k; cin >> n >> k;
  VI a(n);
  REP(i, n) cin >> a[i];
  
  VI ans = solve(n, k, a);
  dumpv(ans);
}

