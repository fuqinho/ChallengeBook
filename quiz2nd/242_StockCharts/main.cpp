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

class BipartGraph {
public:
  BipartGraph(int n) {
    G = VVI(n);
    match = VI(n);
    used = vector<bool>(n);
  }
  void AddEdge(int u, int v) {
    G[u].push_back(v);
    G[v].push_back(u);
  }
  int MaxMatch() {
    fill(ALL(match), -1);
    int res = 0;
    REP(i, G.size()) {
      if (match[i] < 0) {
        fill(ALL(used), false);
        if (dfs(i)) res++;
      }
    }
    return res;
  }
private:
  VVI G;
  VI match;
  vector<bool> used;
  bool dfs(int v) {
    used[v] = true;
    REP(i, G[v].size()) {
      int u = G[v][i];
      if (match[u] < 0 || (!used[match[u]] && dfs(match[u]))) {
        match[v] = u;
        match[u] = v;
        return true;
      }
    }
    return false;
  }
};

bool isOver(VI& a, VI& b) {
  REP(i, a.size()) {
    if (a[i] <= b[i]) return false;
  }
  return true;
}

int solve(int n, int k, VVI& prices) {
  BipartGraph graph(n * 2);
  REP(i, n) {
    REP(j, n) {
      if (i != j) {
        if (isOver(prices[j], prices[i])) {
          //cerr << "Add Edge: " << i << " -> " << j << endl;
          graph.AddEdge(i, n + j);
        }
      }
    }
  }
  //cerr << "Max Match: " << graph.MaxMatch() << endl;
  return n - graph.MaxMatch();
}

int main() {
  int T; cin >> T;
  for (int t = 1; t <= T; t++) {
    int n, k; cin >> n >> k;
    VVI prices(n, VI(k));
    REP(i, n) {
      REP(j, k) cin >> prices[i][j];
    }

    int ans = solve(n, k, prices);
    cout << "Case #" << t << ": " << ans << endl;
  }
}

