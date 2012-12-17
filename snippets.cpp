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


// 深さ優先探索
// 再帰やstackを利用して深さ方向を優先した全探索。
// コード略。

// 幅優先探索
// queue等を利用して幅方向を優先した全探索。
// コード略。

// メモ化再帰
// 再帰で計算する途中、同じ入力から得られる出力をメモして再利用する。
// コード略。

// 動的計画法
// 漸化式を立てることで、再帰を用いずに計算済みの結果を再利用する。
// コード略。

// UnionFind木
// 要素が同じ集合に入っているかの判定と、集合同士の結合を高速に行う。
class UnionFindTree {
public:
    UnionFindTree(int n) {
        rank = vector<int>(n, 0);
        p = vector<int>(n);
        for (int i = 0; i < n; i++) p[i] = i;
    }
    int find(int x) {
        if (x != p[x]) p[x] = find(p[x]);
        return p[x];
    }
    void unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rank[rx] < rank[ry]) p[rx] = ry;
        else {
            p[ry] = rx;
            if (rank[rx] == rank[ry]) rank[rx]++;
        }
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
private:
    vector<int> p;
    vector<int> rank;
};

// ベルマンフォード法
// 最短経路を求める。辺に負が含まれていてもOK

// ダイクストラ法
// より効率よく最短経路を求める。辺に負はNG

// ワーシャルフロイド法
// 任意の2点間の最短距離をDPで一気に求める。辺に負が含まれていてもOK

// プリム法
// ダイクストラ法と似た手法で最小全域木を求める

// クラスカル法
// 短い辺から繋いでいって最小全域木を求める。UnionFindTree利用。


// ユークリッドの互除法
// a, b (a > b)の最大公約数を返す
int gcd(int a, int b) {
  if (b == 0) return a;
  else return gcd(b, a % b);
}

// 拡張ユークリッドの互除法
// a, b (a > b)の最大公約数を求めると同時に、
// ax + by = gcd(a,b)を満たすx, yのペアを求める
int extgcd(int a, int b, int& x, int& y) {
  int d = a;
  if (b != 0) {
    d = extgcd(b, a % b, y, x);
    y -= (a / b) * x;
  } else {
    x = 1; y = 0;
  }
  return d;
}

// エラトステネスのふるい
// n以下の素数のリストを返す
vector<int> getPrimes(int n) {
  vector<int> is_prime(n + 1, true);
  vector<int> res;
  for (int i = 2; i <= n; i++) {
    if (is_prime[i]) {
      res.push_back(i);
      for (int j = i * 2; j <= n; j += i) is_prime[j] = false;
    }
  }
  return res;
}

// 素数判定
bool is_prime(int n) {
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) return false;
  }
  return n != 1;
}

// 素因数分解
map<int, int> prime_factor(int n) {
  map<int, int> res;
  for (int i = 2; i * i <= n; i++) {
    while (n % i == 0) {
      ++res[i];
      n /= i;
    }
  }
  if (n != 1) res[n] = 1;
  return res;
}

// 約数の列挙
vector<int> divisor(int n) {
  vector<int> res;
  for (int i = 1; i * i <= n; i++) {
    if (n % i == 0) {
      res.push_back(i);
      if (i != n / i) res.push_back(n / i);
    }
  }
  return res;
}

/////////////////////////////////////
//// 合同式
const int MOD = 1000000007;

int mod(long long a) {
  return (a % MOD + MOD) % MOD;
}

int mod_add(int a, int b) {
  return mod(a + b);
}

int mod_sub(int a, int b) {
  return mod(a - b);
}

int mod_mul(int a, int b) {
  return mod((long long)a * b);
}

int mod_pow(int a, int e) {
  int res = 1;
  int t = a;
  while (e > 0) {
    if (e & 1) res = mod_mul(res, t);
    t = mod_mul(t, t);
    e >>= 1;
  }
  return res;
}

int mod_div(int a, int b) {
  return mod_mul(a, mod_pow(b, MOD-2));
}

//// 合同式の値用クラス
struct mint {
    static const int n = 1000000007;
    int v;
    mint() : v(0) {}
    mint(int v) : v(v) {}
    mint& operator+= (const mint& o) {v = (v+o.v)%n; return *this;}
    mint& operator-= (const mint& o) {v = (v-o.v+n)%n; return *this;}
    mint& operator*= (const mint& o) {v = ((long long)v*o.v)%n; return *this;}
    mint& operator/= (const mint& o) {v = (o.inv()*=v).v; return *this;}
    mint inv() const {return (*this).pow(n-2);}
    mint pow(int e) const {
        mint res=1, x=v;
        while (e) {if (e&1) res*=x; x*=x; e>>=1;}
        return res;
    }
};
mint operator+(const mint& x, const mint& y) {return (x.v+y.v)%mint::n;}
mint operator-(const mint& x, const mint& y) {return (x.v-y.v+mint::n)%mint::n;}
mint operator*(const mint& x, const mint& y) {return ((long long)x.v*y.v)%mint::n;}
mint operator/(const mint& x, const mint& y) {return x*y.inv();}
std::ostream& operator<<(std::ostream& os, const mint& x) {return os<<x.v;}

////////////////////////////////////
int combination(int n, int r) {
  int res = 1;
  r = min(r, n-r);
  for (int i = 0; i < r; i++) {
    res = mod_mul(res, n-i);
    res = mod_div(res, i+1);
  }
  return res;
}

int homogeneous(int n, int r) {
  return combination(n+r-1, n);
}
///////////////////////////////////////




// 合同式のべき乗: x^n (mod m)
LL mod_pow(LL x, LL n, LL m) {
  if (n == 0) return 1;
  LL res = mod_pow(x * x % m, n / 2, m);
  if (n & 1) res = res * x % m;
  return res;
}

// 合同式の掛け算(オーバーフロー対策): a*b (mod m)
LL mod_mult(LL a, LL b, LL m) {
  LL res = 0;
  LL exp = a % m;
  while (b) {
    if (b & 1) {
      res += exp;
      if (res > m) res -= m;
    }
    exp <<= 1;
    if (exp > m) exp -= m;
    b >>= 1;
  }
  return res;
}

// ミラー-ラビン素数判定法
bool miller_rabin(LL n, LL times) {
  if (n < 2) return false;
  if (n == 2) return true;
  if (!(n & 1)) return false;

  LL q = n-1;
  int k = 0;
  while (q % 2 == 0) {
    k++;
    q >>= 1;
  }
  // n - 1 = 2^k * q (qは奇素数)
  // nが素数であれば、下記のいずれかを満たす
  // (i) a^q ≡ 1 (mod n)
  // (ii) a^q, a^2q,..., a^(k-1)q のどれかがnを法として-1
  //
  // なので、逆に(i)(ii)いずれも満たしていない時は合成数と判定できる
  //
  for (int i = 0; i < times; i++) {
    LL a = rand() % (n-1) + 1; // 1,..,n-1からランダムに値を選ぶ
    LL x = mod_exp(a, q, n);
    // (i)をチェック
    if (x == 1) continue;
    // (ii)をチェック
    bool found = false;
    for (int j = 0; j < k; j++) {
      if (x == n-1) {
        found = true;
        break;
      }
      x = mod_mult(x, x, n);
    }
    if (found) continue;

    return false;
  }
  return true;
}

// ポラード・ロー素因数分解法
// nが合成数とわかってる時に、その約数を見つける
LL get_gcd(LL n, LL m) {
  if (n < m) swap(n, m);
  while (m) {
    swap(n, m);
    m %= n;
  }
  return n;
}
LL pollard_rho(LL n, int c) {
  LL x = 2;
  LL y = 2;
  LL d = 1;
  while (d == 1) {
    x = mod_mult(x, x, n) + c;
    y = mod_mult(y, y, n) + c;
    y = mod_mult(y, y, n) + c;
    d = get_gcd((x-y >= 0 ? x-y : y-x), n);
  }
  if (d == n) return pollard_rho(n, c+1);
  return d;
}

// 繰り返し二乗法

// 行列の掛け算
vector<vector<int> > mul(vector<vector<int> >& a, vector<vector<int> >& b) {
  int row_num = a.size(), col_num = b[0].size();
  vector<vector<int> > res(row_num, vector<int>(col_num, 0));
  for (int i = 0; i < row_num; i++) {
    for (int j = 0; j < col_num; j++) {
      for (int k = 0; k < a[0].size(); k++) {
        res[i][j] += a[i][k] * b[k][j];
      }
    }
  }
  return res;
}

// セグメント木: RMQ(Range Minimum Query)
// 区間に対する演算を、各サブ区間の演算結果をキャッシュすることで高速に行う


// Binary Indexed Tree
struct BIT {
  vector<LL> bit;
  BIT(int n) {
    bit = vector<LL>(n+1);
  }
  LL sum(int i) {
    LL res = 0;
    while (i > 0) {
      res += bit[i];
      i -= (i & -i);
    }
    return res;
  }
  LL sum(int i, int j) {
    return sum(j) - sum(i-1);
  }
  void add(int i, LL x) {
    while (i < bit.size()) {
      bit[i] += x;
      i += (i & -i);
    }
  }
};

// Ford-Fulkderson
class FordFulkerson {
public:
  FordFulkerson(int nElement) {
    m_edges = vector< vector<Edge> >(nElement);
    m_used = vector<bool>(nElement, false);
  }
  void addEdge(int from, int to, int cap) {
    m_edges[from].push_back(Edge(to, cap, m_edges[to].size()));
    m_edges[to].push_back(Edge(from, 0, m_edges[from].size()-1));
  }
  int maxFlow(int s, int t) {
    int flow = 0;
    for (;;) {
      fill(m_used.begin(), m_used.end(), false);
      int f = dfs(s, t, 100000);
      if (f > 0) flow += f;
      else break;
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
  vector<bool> m_used;
  int dfs(int v, int t, int f) {
    if (v == t) return f;
    m_used[v] = true;
    for (int i = 0; i < m_edges[v].size(); i++) {
      Edge& e = m_edges[v][i];
      if (e.cap > 0 && m_used[e.to] == false) {
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

// Dinic
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
      bfs(s);
      if (m_level[t] < 0) break;
      fill(m_iter.begin(), m_iter.end(), 0);
      int f = 0;
      while ((f = dfs(s, t, INF)) > 0) {
        flow += f;
      }
    }
    return flow;
  }
private:
  struct Edge {
    int to, cap, rev;
    Edge(int t, int c, int r):to(t),cap(c),rev(r){}
  };
  static const int INF = 1000000000;
  vector< vector<Edge> > m_edges;
  vector<int> m_level;
  vector<int> m_iter;
  void bfs(int s) {
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

// 2部グラフのマッチング
class BipartGraph {
public:
  BipartGraph(int n) {
    G = VVI(n);
    match = VI(n);
    used = vector<bool>(n);
  }
  void AddEdge(int u, int v) {
    G[u].push_back(v);
    G[v].push_back(u);
  }
  int MaxMatch() {
    fill(ALL(match), -1);
    int res = 0;
    REP(i, G.size()) {
      if (match[i] < 0) {
        fill(ALL(used), false);
        if (dfs(i)) res++;
      }
    }
    return res;
  }
private:
  VVI G;
  VI match;
  vector<bool> used;
  bool dfs(int v) {
    used[v] = true;
    REP(i, G[v].size()) {
      int u = G[v][i];
      if (match[u] < 0 || (!used[match[u]] && dfs(match[u]))) {
        match[v] = u;
        match[u] = v;
        return true;
      }
    }
    return false;
  }
};

// Minimum Cost Flow
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


// 凸包(グラハムスキャン)

// 凸包(キャリパー法)


// Ax = bを解く
vector<double> gauss_jordan(const vector<vector<double> >& A, const vector<double>& b) {
  int n = A.size();
  vector<vector<double> > B(n, vector<double>(n+1));
  REP(i, n) REP(j, n) B[i][j] = A[i][j];
  REP(i, n) B[i][n] = b[i];

  REP(i, n) {
    int pivot = i;
    for (int j = i; j < n; j++) {
      if (abs(B[j][i]) > abs(B[pivot][i])) pivot = j;
    }
    swap(B[i], B[pivot]);

    if (abs(B[i][i]) < EPS) return vector<double>();

    for (int j = i+1; j <= n; j++) B[i][j] /= B[i][i];
    B[i][i] = 1; // not necessary

    REP(j, n) {
      if (i != j) {
        for (int k = i+1; k <= n; k++) {
          B[j][k] -= B[j][i] * B[i][k];
        }
        B[j][i] = 0; // not necessary
      }
    }
  }
  vector<double> res(n);
  REP(i, n) res[i] = B[i][n];

  return res;
}

// Z algorithm
vector<int> zfunction(string& s) {
  int n = s.size();
  int L = 0, R = 0;
  vector<int> z(n, 0);
  for (int i = 1; i < n; i++) {
    if (i > R) {
      L = R = i;
      while (R < n && s[R-L] == s[R]) R++;
      z[i] = R-L;
      R--;
    } else {
      int k = i-L;
      if (z[k] <= R-i) {
        z[i] = z[k];
      } else {
        L = i;
        while (R < n && s[R-L] == s[R]) R++;
        z[i] = R-L;
        R--;
      }
    }
  }
  return z;
}

/////////////////////////////////////
// 幾何

// 角度の正規化 [-PI, PI)
double normalize(double theta) {
  if(theta < 0.0) theta = -theta;
  int n = theta / 2.0 / PI;
  theta -= 2.0 * PI * n;
  if(theta > PI) theta = 2.0 * PI - theta;
  return theta;
}

// テスト用main関数
int main() {

}
