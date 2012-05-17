#include <iostream>
#include <vector>
using namespace std;

struct Edge {
  int to, cap, cost, rev;
  Edge(int to, int cap, int cost, int rev)
    : to(to), cap(cap), cost(cost), rev(rev) {}
};

static const int INF = 1000000;
static const int MAX_V = 10;
int V = 5;
vector<Edge> G[MAX_V];


// 直前の頂点と辺
int prev_v[MAX_V], prev_e[MAX_V];

void add_edge(int from, int to, int cap, int cost) {
  G[from].push_back(Edge(to, cap, cost, G[to].size()));
  G[to].push_back(Edge(from, 0, -cost, G[from].size()-1));
}

int min_cost_flow(int s, int t, int f) {

  vector<int> dist(V);
  int res = 0;

  while (f > 0) {
    // ベルマンフォード方でs-t間最短路を求める
    fill(dist.begin(), dist.end(), INF);
    dist[s] = 0;
    bool update = true;
    while (update) {
      update = false;
      for (int v = 0; v < V; v++) {
        if (dist[v] == INF) continue;
        for (int i = 0; i < G[v].size(); i++) {
          Edge& e = G[v][i];
          if (e.cap > 0 && dist[e.to] > dist[v] + e.cost) {
            dist[e.to] = dist[v] + e.cost;
            prev_v[e.to] = v;
            prev_e[e.to] = i;
            update = true;
          }
        }
      }
    }

    // tまでのパスがなくなればこれ以上流せない
    if (dist[t] == INF) return -1;

    // s-t間最短路に沿って目一杯流す
    int d = f;
    for (int v = t; v != s; v = prev_v[v]) {
      d = min(d, G[prev_v[v]][prev_e[v]].cap);
    }
    f -= d;
    res += d * dist[t];
    for (int v = t; v != s; v = prev_v[v]) {
      Edge& e = G[prev_v[v]][prev_e[v]];
      e.cap -= d;
      G[v][e.rev].cap += d;
    }
  }
  return res;
}


int main() {
  add_edge(0, 1, 10, 2);
  add_edge(0, 2, 2, 4);
  add_edge(1, 2, 6, 6);
  add_edge(1, 3, 6, 2);
  add_edge(2, 4, 5, 2);
  add_edge(3, 2, 3, 3);
  add_edge(3, 4, 8, 6);

  int ans = min_cost_flow(0, 4, 9);
  cout << ans << endl;
}
