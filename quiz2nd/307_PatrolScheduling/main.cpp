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



int main() {
  int N, M; cin >> N >> M;
  VI s(N), t(N);
  REP(i, N) cin >> s[i] >> t[i];
  REP(i, N) if (t[i] < s[i]) t[i] += M;


  // 簡単のため、来週の分までの放送予定をsecにつっこむ。
  // pair<終了時刻, 開始時刻>の順にした上で、終了時刻が速い順にソート
  vector<PII> sec;
  REP(i, N) {
    sec.push_back(make_pair(t[i], s[i]));
    sec.push_back(make_pair(t[i]+M, s[i]+M));
  }
  sort(ALL(sec));

  dumpv(sec);

  // 区間の端点をソート
  vector<PII> ps(sec.size() * 2);
  for (int i = 0; i < sec.size(); i++) {
    ps[i] = make_pair(sec[i].first, i); // 始点
    ps[i+sec.size()] = make_pair(sec[i].second, i+sec.size()); // 終点
  }
  sort(ALL(ps));

  dumpv(ps);


  const int MAX_N = 100000;
  const int MAX_LOG_N = int(log2(MAX_N)) + 1;
  dump(MAX_LOG_N);


  // next[0][3]: 3番目のsecの次に選ぶsec
  // next[1][3]: 3番目のsecの2個後に選ぶsec
  // next[2][3]: 3番目のsecの4個後に選ぶsec
  VVI next(MAX_LOG_N, VI(MAX_N, 0));
  int last = -1;
  for (int i = ps.size()-1; i >= 0; i--) {
    int idx = ps[i].second % sec.size();
    // 始点
    if (ps[i].second >= sec.size()) {
      last = idx;
      dump(last);
    }
    // 終点
    else {
      cerr << "next[" << idx << "] = " << last << endl;
      next[0][idx] = last;
    }
  }

  for (int k = 1; k < MAX_LOG_N; k++) {
    REP(i, sec.size()) {
      if (next[k-1][i] < 0)
        next[k][i] = -1;
      else
        next[k][i] = next[k-1][next[k-1][i]];
    }
  }

  REP(k, 10) {
    REP(i, sec.size()) cerr << next[k][i] << " "; cerr << endl;
  }

  int ans = 0;
  // 最初の区間を固定
  REP(i, N) {
    int start = sec[i].second;
    dump(sec[i].second + M);
    // 二分探索を使う
    int tmp = 0, j = i;
    for (int k = MAX_LOG_N-1; k >= 0; k--) {
      int j2 = next[k][j];
      if (j2 >= 0 && sec[j2].first <= start + M) {
      dump(sec[j2].first);
        j = j2;
        tmp |= 1 << k;
      }
    }
    ans = max(ans, tmp + 1);
  }

  dump(ans);
}

