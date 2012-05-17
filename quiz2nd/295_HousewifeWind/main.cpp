// !!!! Time Limit Exceeded !!!!
// 再帰をスタック使ったループに書き換えたり、とかしないといけないかも

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
#include <climits>
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

struct RMQ {
  RMQ(int v[], int n) {
    elem_size = 1;
    while (elem_size < n) elem_size *= 2;
    orig = VI(elem_size, INT_MAX);
    dat = VI(elem_size * 2 - 1, -1);

    REP(i, n) {
      orig[i] = v[i];
      dat[i + elem_size - 1] = i;
    }
    update(0);
    //REP(i, n) cerr << orig[i] << " "; cerr << endl;
    //REP(i, n*2-1) cerr << dat[i] << " "; cerr << endl;
  }
  int update(int k) {
    if (k < elem_size - 1 && dat[k] == -1) {
      int il = update(k*2+1);
      int ir = update(k*2+2);

      if (il == -1 && ir == -1) return -1;
      if (il == -1 && ir != -1) return dat[k] = ir;
      if (il != -1 && ir == -1) return dat[k] = il;
      dat[k] = (orig[il] <= orig[ir] ? il : ir);
    }
    return dat[k];
  }

  void update(int k, int a) {
    orig[k] = a;
    k += elem_size - 1;
    while (k > 0) {
      k = (k-1) / 2;
      dat[k] = (orig[dat[k*2+1]] <= orig[dat[k*2+2]] ? dat[k*2+1] : dat[k*2+2]);
    }
  }

  int query(int a, int b) {
    return query(a, b, 0, 0, elem_size);
  }

  int query(int a, int b, int k, int l, int r) {
    if (r <= a || b <= l) return -1;
    if (a <= l && r <= b) return dat[k];
    
    int il = query(a, b, k*2+1, l, (l+r)/2);
    int ir = query(a, b, k*2+2, (l+r)/2, r);
    
    if (il != -1 && ir != -1) {
      return orig[il] <= orig[ir] ? il : ir;
    } else {
      return max(ir, il);
    }
  }
  int elem_size;
  VI dat;
  VI orig;
};



int V;
struct edge {int id, to, cost;};

// constraint
const int MAX_V = 100000;
const int MAX_Q = 100000;

// input data
int n, q, s;
int a[MAX_V - 1], b[MAX_V - 1], w[MAX_V - 1];
int type[MAX_Q];
int x[MAX_Q], t[MAX_Q];

// グラフ
vector<edge> G[MAX_V];
int root;

int vs[MAX_V * 2 - 1]; // DFSでの訪問順
int depth[MAX_V * 2 - 1]; // 根からの深さ
int id[MAX_V]; // 各頂点がeに初めて登場するインデックス
int es[(MAX_V - 1) * 2]; // 辺のインデックス(i*2 + (葉方向:0,根方向:1))

int bit[MAX_V * 2 - 1];
int bit_n;

int sum(int i) {
  int s = 0;
  while (i > 0) {
    s += bit[i];
    i -= i & -i;
  }
  return s;
}

void add(int i, int x) {
  while (i <= bit_n) {
    bit[i] += x;
    i += i & -i;
  }
}

void dfs(int v, int p, int d, int &k) {
  id[v] = k;
  vs[k] = v;
  depth[k] = d;
  k++;
  REP(i, G[v].size()) {
    edge& e = G[v][i];
    if (e.to != p) {
      add(k, e.cost);
      es[e.id * 2] = k;
      dfs(e.to, v, d + 1, k);
      vs[k] = v;
      depth[k] = d;
      k++;
      add(k, -e.cost);
      es[e.id * 2 + 1] = k;
    }
  }
}


int main() {
  // read input data
  scanf("%d %d %d", &n, &q, &s);
  REP(i, n-1) scanf("%d %d %d", &a[i], &b[i], &w[i]);
  REP(i, q) {
    scanf("%d", &type[i]);
    if (type[i] == 0) scanf("%d", &x[i]);
    else scanf("%d %d", &x[i], &t[i]);
  }

  // グラフGを構成する
  REP(i, n-1) {
    G[a[i]-1].push_back((edge){i, b[i]-1, w[i]});
    G[b[i]-1].push_back((edge){i, a[i]-1, w[i]});
  }

  root = n / 2;

  // BITを初期化する
  //BIT bit((n - 1) * 2);
  bit_n = (n-1) * 2;
  

  // vs, depth, id, esを初期化する
  int k = 0;
  dfs(root, -1, 0, k);

  /*
  // RMQを初期化する
  RMQ rmq(n * 2 - 1);

  // RMQにdepthの値を入れる
  REP(i, n*2-1) rmq.update(i, depth[i]);
  */
  RMQ rmq(depth, n*2-1);

  // クエリを処理
  int v = s - 1;
  REP(i, q) {
    if (type[i] == 0) {
      int u = x[i] - 1;
      // 経由する最短の親を求める
      int lca = rmq.query(min(id[u], id[v]), max(id[u], id[v]) + 1);
      int p = vs[lca];
      int distance = sum(id[v]) + sum(id[u]) - sum(id[p]) * 2;
      printf("%d\n", distance);
      v = u;
    } else {
      // x[i]番の道路のコストをt[i]に変更
      int k = x[i] - 1;
      add(es[k * 2], t[i] - w[k]);
      add(es[k * 2 + 1], w[k] - t[i]);
      w[k] = t[i];
    }
  }
}

