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

int V;
const int MAX_V = 6402;

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
    int u = G[v][i];
    int w = match[u];
    if (w < 0 || (!used[w] && dfs(w))) {
      match[v] = u;
      match[u] = v;
      return true;
    }
  }
  return false;
}

int bipartite_matching() {
  int res = 0;
  memset(match, -1, sizeof(match));
  for (int v = 0; v < V; v++) {
    if (match[v] < 0) {
      memset(used, 0, sizeof(used));
      if (dfs(v)) res++;
    }
  }
  return res;
}

int solve(int M, int N, VS& seats) {
  int vNum = 0;
  V = M * N;
  REP(i, V) G[i].clear();
  REP(i, M) {
    REP(j, N) {
      if (seats[i][j] != 'x') {
        vNum++;
        if (j+1 < N) {
          if (seats[i][j+1] != 'x') add_edge(i*N + j, i*N + (j+1));
          if (i-1 >= 0 && seats[i-1][j+1] != 'x') add_edge(i*N + j, (i-1)*N + (j+1));
        }
        if (j-1 >= 0) {
          if (i-1 >= 0 && seats[i-1][j-1] != 'x') add_edge(i*N + j, (i-1)*N + (j-1));
        }
      }
    }
  }
  // |最大マッチング| = |最小点被覆|
  int minCover = bipartite_matching();

  // |最大安定集合| = V - |最小点被覆|
  return vNum - minCover;
}

int main() {
  int T; cin >> T;
  REP(t, T) {
    int M, N; cin >> M >> N;
    VS seats(M);
    REP(i, M) cin >> seats[i];

    int ans = solve(M, N, seats);
    cout << "Case #" << (t+1) << ": " << ans << endl;
  }
}

