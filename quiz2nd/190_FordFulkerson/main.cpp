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
#include <cstdio>
#include <cmath>
#include <cstring>
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
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& stream, const std::pair<T1, T2>& data) {
  return stream << "(" << data.first << "," << data.second << ")";
}

static const int INF = 1000000000;
static const int MAX_V = 100;

struct edge {
  int to; // 行き先のNodeのIndex
  int cap; // このエッジの容量
  int rev; // 逆辺の行き先ノード内での辺のインデックス
};

vector<edge> G[MAX_V];
bool used[MAX_V]; // dfsですでに調べたかのフラグ

// fromからtoへ向かう容量capの辺をグラフに追加する
void add_edge(int from, int to, int cap) {
  G[from].push_back((edge){to, cap, G[to].size()});
  G[to].push_back((edge){from, 0, G[from].size() - 1});
}

// 増加パスをdfsで探す
// v:source t:sink f:流せる最大量
int dfs(int v, int t, int f) {
  // v == tなら、fだけ流せる
  if (v == t) return f;

  // この辺は（今回のDFSでは）使った
  used[v] = true;

  // node vからの各辺に対して…
  for (int i = 0; i < G[v].size(); i++) {
    edge& e = G[v][i];

    // 行き先のノードが未使用で、このエッジのcapacityが残っていれば
    if (!used[e.to] && e.cap > 0) {
      
      // 行き先ノードからゴールまでの流れる量を求める(再帰的に)
      int d = dfs(e.to, t, min(f, e.cap));

      // もし多少なりとも流せるならそのエッジを採用して、流せる量dを返す
      if (d > 0) {
        // このエッジのキャパを減らして、
        e.cap -= d;
        // 逆方向のエッジのキャパを増やす
        G[e.to][e.rev].cap += d;
        return d;
      }
    }
  }

  // 流せるエッジがなければ0
  return 0;
}

int max_flow(int s, int t) {
  int flow = 0;
  for (;;) {
    memset(used, 0, sizeof(used));
    int f = dfs(s, t, INF);
    if (f == 0) return flow;
    flow += f;
  }
  return flow;
}

int main() {
  add_edge(0, 1, 10);
  add_edge(0, 2, 2);
  add_edge(1, 2, 6);
  add_edge(1, 3, 6);
  add_edge(2, 4, 5);
  add_edge(3, 2, 3);
  add_edge(3, 4, 8);

  int ans = max_flow(0, 4);
  cout << ans << endl;
}

