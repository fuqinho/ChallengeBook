#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>
using namespace std;

class MinCostFlowGraph {
public:
  MinCostFlowGraph(int n) : INF(100000000) {
    G = vector<vector<edge> >(n);
    h = vector<int>(n);
    dist = vector<int>(n);
    prevv = vector<int>(n);
    preve = vector<int>(n);
  }
  void add_edge(int from, int to, int cap, int cost) {
    G[from].push_back(edge(to, cap, cost, G[to].size()));
    G[to].push_back(edge(from, 0, -cost, G[from].size()-1));
  }
  int min_cost_flow(int s, int t, int f) {
    int res = 0;
    fill(h.begin(), h.end(), 0);
    while (f > 0) {
      priority_queue<PII, vector<PII>, greater<PII> > que;
      fill(dist.begin(), dist.end(), INF);
      dist[s] = 0;
      que.push(PII(0, s));
      while (!que.empty()) {
        PII p = que.top(); que.pop();
        int v = p.second;
        if (dist[v] >= p.first) {
          for (int i = 0; i < G[v].size(); i++) {
            edge& e = G[v][i];
            if (e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]) {
              dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
              prevv[e.to] = v;
              preve[e.to] = i;
              que.push(PII(dist[e.to], e.to));
            }
          }
        }
      }
      if (dist[t] == INF) return -1;
      for (int v = 0; v < h.size(); v++) h[v] += dist[v];
      int d = f;
      for (int v = t; v != s; v = prevv[v]) d = min(d, G[prevv[v]][preve[v]].cap);
      f -= d;
      res += d * h[t];
      for (int v = t; v != s; v = prevv[v]) {
        edge& e = G[prevv[v]][preve[v]];
        e.cap -= d;
        G[v][e.rev].cap += d;
      }
    }
    return res;
  }
private:
  const int INF;
  typedef pair<int, int> PII;
  struct edge {
    int to, cap, cost, rev;
    edge(int t, int ca, int co, int r):to(t),cap(ca),cost(co),rev(r){}
  };
  vector<vector<edge> > G;
  vector<int> h, dist, prevv, preve;
};

int main() {
  int N, M; scanf("%d %d", &N, &M);
  MinCostFlowGraph graph(N);
  for (int i = 0; i < M; i++) {
    int a, b, c; scanf("%d %d %d", &a, &b, &c);
    graph.add_edge(a-1, b-1, 1, c);
    graph.add_edge(b-1, a-1, 1, c);
  }

  int ans = graph.min_cost_flow(0, N-1, 2);
  cout << ans << endl;
}
