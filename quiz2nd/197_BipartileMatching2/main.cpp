#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int V = 6;
static const int MAX_V = 10;
vector<int> G[MAX_V];
int match[MAX_V];
bool used[MAX_V];

void add_edge(int u, int v) {
  G[u].push_back(v);
  G[v].push_back(u);
}

bool dfs(int v) {
  used[v] = true;
  for (int i = 0; i < G[v].size(); i++) {
    int u = G[v][i], w = match[u];
    if (w < 0 || (!used[w] && dfs(w))) {
      match[v] = u;
      match[u] = v;
      return true;
    }
  }
  return false;
}

int bipartite_matching()
{
  int res = 0;
  memset(match, -1, sizeof(match));
  for (int v = 0; v < V; v++) {
    if (match[v] < 0) {
      memset(used, 0, sizeof(used));
      if (dfs(v)) {
        res++;
      }
    }
  }
  return res;
}

int main()
{
  add_edge(0, 3);
  add_edge(0, 4);
  add_edge(1, 3);
  add_edge(1, 5);
  add_edge(2, 4);

  int ans = bipartite_matching();
  cout << ans << endl;
}
