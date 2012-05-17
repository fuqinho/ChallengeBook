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

const int MAX_W = 10000;

int dp[MAX_W + 1];

int main() {
  int n, W; cin >> n >> W;
  VI w(n), v(n), m(n);
  REP(i, n) cin >> w[i] >> v[i] >> m[i];

  REP(i, n) {
    REP(a, w[i]) {
      deque<PII> deq; // pair<index, value>
      
      // w[i]で割ってa余る重さに対して更新処理
      for (int j = 0; j * w[i] + a <= W; j++) {
        // デックの末尾にjを追加
        int val = dp[j * w[i] + a] - j * v[i];
        while (!deq.empty() && deq.back().second <= val) deq.pop_back();
        deq.push_back(PII(j, val));

        // 先頭に(j-m[i])*w[i]+a ~ j*w[i]+aまでの最大値が入っているのでそれを使ってdp更新
        dp[j * w[i] + a] = deq.front().second + j * v[i];

        // 取り出したのが次回は範囲外になる分ならdequeから抜く
        if (deq.front().first == j - m[i]) {
          deq.pop_front();
        }
      }
    }
  }

  printf("%d\n", dp[W]);
}

