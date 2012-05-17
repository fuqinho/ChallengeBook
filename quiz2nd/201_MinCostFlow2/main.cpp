#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
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

  int res = 0;
  vector<int> dist(V);

  // h[v]: 残余グラフ上でのs-v間の最短距離
  vector<int> h(V, 0);

  while (f > 0) {
    // ダイクストラ法を用いてhを更新する
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > que;
    fill(dist.begin(), dist.end(), INF);
    dist[s] = 0;
    que.push(make_pair(0, s));
    while (!que.empty()) {
      pair<int, int> p = que.top(); que.pop();
      int v = p.second;
      if (dist[v] < p.first) continue;
      for (int i = 0; i < G[v].size(); i++) {
        Edge& e = G[v][i];
        if (e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]) {
          dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
          prev_v[e.to] = v;
          prev_e[e.to] = i;
          que.push(make_pair(dist[e.to], e.to));
        }
      }
    }

    /*
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
    */

    // tまでのパスがなくなればこれ以上流せない
    if (dist[t] == INF) return -1;

    for (int v = 0; v < V; v++) h[v] += dist[v];

    // s-t間最短路に沿って目一杯流す
    int d = f;
    for (int v = t; v != s; v = prev_v[v]) {
      d = min(d, G[prev_v[v]][prev_e[v]].cap);
    }
    f -= d;
    //res += d * dist[t];
    res += d * h[t];
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
