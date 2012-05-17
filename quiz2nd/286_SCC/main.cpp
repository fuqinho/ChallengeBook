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

const int MAX_V = 20;

int V;
VI G[MAX_V];
VI rG[MAX_V];
bool used[MAX_V];
VI vs;
int cmp[MAX_V];

void add_edge(int from, int to) {
  G[from].push_back(to);
  rG[to].push_back(from);
}

void dfs(int v) {
  used[v] = true;
  REP(i, G[v].size()) {
    if (!used[G[v][i]]) dfs(G[v][i]);
  }
  vs.push_back(v);
}

void rdfs(int v, int k) {
  used[v] = true;
  cmp[v] = k;
  REP(i, rG[v].size()) {
    if (!used[rG[v][i]]) rdfs(rG[v][i], k);
  }
}

int main() {
  V = 12;
  // construct
  add_edge(0, 1);
  add_edge(1, 2);
  add_edge(1, 3);
  add_edge(2, 3);
  add_edge(3, 4);
  add_edge(4, 2);
  add_edge(4, 5);
  add_edge(5, 6);
  add_edge(6, 7);
  add_edge(6, 8);
  add_edge(6, 9);
  add_edge(7, 5);
  add_edge(8, 10);
  add_edge(9, 8);
  add_edge(9, 11);
  add_edge(10, 8);


  // DFS 1
  fill(used, used+V, false);
  REP(i, V) {
    if (!used[i]) dfs(i);
  }
  dumpv(vs);


  // DFS 2
  fill(used, used+V, false);
  int k = 0;
  for (int i = vs.size()-1; i >= 0; --i) {
    if (!used[vs[i]]) {
      rdfs(vs[i], k);
      k++;
    }
  }

  REP(i, V) cerr << cmp[i] << " ";
  cerr << endl;
}

