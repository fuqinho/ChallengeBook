#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Dinic {
public:
  Dinic(int nElement) {
    m_edges = vector< vector<Edge> >(nElement);
    m_level = vector<int>(nElement);
    m_iter = vector<int>(nElement);
  }
  void addEdge(int from, int to, int cap) {
    m_edges[from].push_back(Edge(to, cap, m_edges[to].size()));
    m_edges[to].push_back(Edge(from, 0, m_edges[from].size()-1));
  }
  int maxFlow(int s, int t) {
    int flow = 0;
    for (;;) {
      calcLevels(s);
      if (m_level[t] < 0) break;
      fill(m_iter.begin(), m_iter.end(), 0);
      int f = 0;
      while ((f = dfs(s, t, 10000)) > 0) {
        flow += f;
      }
    }
    return flow;
  }
private:
  struct Edge {
    int to, cap, rev;
    Edge(int to, int cap, int rev)
      : to(to), cap(cap), rev(rev) {}
  };
  vector< vector<Edge> > m_edges;
  vector<int> m_level;
  vector<int> m_iter;

  void calcLevels(int s) {
    fill(m_level.begin(), m_level.end(), -1);
    m_level[s] = 0;
    queue<int> que;
    que.push(s);
    while (que.size() > 0) {
      int v = que.front(); que.pop();
      for (int i = 0; i < m_edges[v].size(); i++) {
        Edge& e = m_edges[v][i];
        if (e.cap > 0 && m_level[e.to] == -1) {
          m_level[e.to] = m_level[v] + 1;
          que.push(e.to);
        }
      }
    }
  }
  int dfs(int v, int t, int f) {
    if (v == t) return f;
    for (int& i = m_iter[v]; i < m_edges[v].size(); i++) {
      Edge& e = m_edges[v][i];
      if (e.cap > 0 && m_level[e.to] > m_level[v]) {
        int d = dfs(e.to, t, min(f, e.cap));
        if (d > 0) {
          e.cap -= d;
          m_edges[e.to][e.rev].cap += d;
          return d;
        }
      }
    }
    return 0;
  }
};


int main() {
  Dinic dinic(8);

  dinic.addEdge(0, 3, 1);
  dinic.addEdge(0, 4, 1);
  dinic.addEdge(1, 3, 1);
  dinic.addEdge(1, 5, 1);
  dinic.addEdge(2, 4, 1);

  // start and end
  dinic.addEdge(6, 0, 1);
  dinic.addEdge(6, 1, 1);
  dinic.addEdge(6, 2, 1);
  dinic.addEdge(3, 7, 1);
  dinic.addEdge(4, 7, 1);
  dinic.addEdge(5, 7, 1);

  int ans = dinic.maxFlow(6, 7);
  cout << ans << endl;
}
