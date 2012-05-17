#include <iostream>
#include <vector>
#include <queue>
using namespace std;

static const int INF = 1000000000;
static const int MAX_V = 100;

struct Edge {
  int to;
  int cap;
  int rev;
  Edge(int to, int cap, int rev) 
    : to(to), cap(cap), rev(rev) {}
};

// G[v]: vから出ているエッジの配列(vector)
vector<Edge> G[MAX_V];

// level[v]: sからvまでの距離
int level[MAX_V];

// iter[v]: 頂点vから出ているエッジを何本調べ終わったか
int iter[MAX_V];

// fromからtoへ向かう容量capの辺をグラフに追加する
void add_edge(int from, int to, int cap) {
  G[from].push_back(Edge(to, cap, G[to].size()));
  G[to].push_back(Edge(from, 0, G[from].size() - 1));
}

// sから各頂点までの最短距離をBFSで計算する
void bfs(int s) {
  memset(level, -1, sizeof(level));
  queue<int> que;
  level[s] = 0;

  que.push(s);
  while (!que.empty()) {
    int v = que.front(); que.pop();
    for (int i = 0; i < G[v].size(); i++) {
      Edge &e = G[v][i];
      if (e.cap > 0 && level[e.to] < 0) {
        level[e.to] = level[v] + 1;
        que.push(e.to);
      }
    }
  }

  cerr << "=====================" << endl;
  for (int i = 0; i < 7; i++) cerr << level[i] << ",";
  cerr << endl;
}


// 増加パスをdfsで探す
// v:source t:sink f:流せる最大量
int dfs(int v, int t, int f) {
  cerr << "# dfs(" << v << ", " << t << ", " << f << ")" << endl;
  cerr << "        iter: ";
  for (int i = 0; i < 7; i++) cerr << iter[i] << ",";
  cerr << endl;

  // v == tなら、fだけ流せる
  if (v == t) return f;

  // node vからの、まだ調べていない各辺に対して…
  // 「i++が呼ばれる」のはつまり、そのエッジから先に増加パスがもう無いということ。
  // (増加パスが見つかったならi++が呼ばれる前にreturnで抜けているはず。)
  for (int& i = iter[v]; i < G[v].size(); i++) {
    Edge& e = G[v][i];
    cerr << "checking... " << v << " -> " << e.to << endl;

    // この辺のcapacityが残っていて、行き先がより始点から遠い頂点なら
    if (e.cap > 0 && level[v] < level[e.to]) {
      
      // 行き先ノードからゴールまでの流れる量を求める(再帰的に)
      int d = dfs(e.to, t, min(f, e.cap));

      cerr << "  found path: " << d << endl;

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
    // sからの最短距離をBFSで計算する
    bfs(s);

    if (level[t] < 0) return flow;
    memset(iter, 0, sizeof(iter));
    int f;
    // 増加パスをDFSで探す
    while ((f = dfs(s, t, INF)) > 0) {
      flow += f;
    }
  }
  return flow;
}


int main() {
  /*
  add_edge(0, 1, 10);
  add_edge(0, 2, 2);
  add_edge(1, 2, 6);
  add_edge(1, 3, 6);
  add_edge(2, 4, 5);
  add_edge(3, 2, 3);
  add_edge(3, 4, 8);

  int ans = max_flow(0, 4);
  cout << ans << endl;
  */
  add_edge(0, 1, 1);
  add_edge(0, 2, 2);
  add_edge(1, 3, 1);
  add_edge(2, 3, 2);
  add_edge(3, 4, 4);
  add_edge(3, 5, 1);
  add_edge(4, 6, 4);
  add_edge(5, 6, 1);

  int ans = max_flow(0, 6);
  cout << ans << endl;

}

