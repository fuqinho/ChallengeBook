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
int N;
vector<int> X, Y, R, S;

class MaxFlowGraph {
public:
  MaxFlowGraph(int n) {
    G = vector<vector<Edge> >(n);
    used = vector<bool>(n);
  }
  void AddEdge(int from, int to, int cap) {
    G[from].push_back((Edge){to, cap, G[to].size()});
    G[to].push_back((Edge){from, 0, G[from].size()-1});
  }
  int MaxFlow(int s, int t) {
    int res = 0;
    while(true) {
      fill(ALL(used), 0);
      int f = dfs(s, t, INF);
      if (f == 0) break;
      res += f;
    }
    return res;
  }
private:
  struct Edge { int to, cap, rev; };
  vector<vector<Edge> > G;
  vector<bool> used;

  int dfs(int v, int t, int f) {
    if (v == t) return f;
    used[v] = true;
    for (int i = 0; i < G[v].size(); i++) {
      Edge& e = G[v][i];
      if (e.cap > 0 && !used[e.to]) {
        int d = dfs(e.to, t, min(f, e.cap));
        if (d > 0) {
          e.cap -= d;
          G[e.to][e.rev].cap += d;
          return d;
        }
      }
    }
    return 0;
  }
};

int solve() {
  MaxFlowGraph graph(N + 2);
  int s = N;
  int t = N + 1;
  int maxScore = 0;
  REP(i, N) {
    if (S[i] > 0) {
      graph.AddEdge(s, i, S[i]);
      graph.AddEdge(i, t, 0);
      maxScore += S[i];
    } else {
      graph.AddEdge(s, i, 0);
      graph.AddEdge(i, t, -S[i]);
    }
  }
  REP(i, N) {
    REP(j, N) {
      if (i != j) {
        if ((X[i]-X[j])*(X[i]-X[j]) + (Y[i]-Y[j])*(Y[i]-Y[j]) <= R[i]*R[i]) {
          //cerr << "Edge: " << i << " -> " << j << endl;
          graph.AddEdge(i, j, INF);
        }
      }
    }
  }
  return maxScore - graph.MaxFlow(s, t);
}

int main() {
  int T; cin >> T;
  REP(t, T) {
    cin >> N;
    X = VI(N);
    Y = VI(N);
    R = VI(N);
    S = VI(N);
    REP(i, N) cin >> X[i] >> Y[i] >> R[i] >> S[i];
    
    int ans = solve();
    cout << "Case #" << (t+1) << ": " << ans << endl;
  }
}

