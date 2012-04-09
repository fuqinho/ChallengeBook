#include <iostream>
#include <vector>

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
    rank = std::vector<int>(n, 0);
    par = std::vector<int>(n);
    for (int i = 0; i < n; i++) par[i] = i;
  }
  int find(int x) {
    if (x == par[x]) return x;
    else return par[x] = find(par[x]);
  }
  void unite(int x, int y) {
    int rx = find(x), ry = find(y);
    if (rank[rx] < rank[ry]) par[rx] = ry;
    else {
      par[ry] = rx;
      if (rank[rx] == rank[ry]) rank[rx]++;
    }
  }
  bool same(int x, int y) {
    return find(x) == find(y);
  }
private:
  std::vector<int> par;
  std::vector<int> rank;
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
std::vector<int> getPrimes(int n) {
  std::vector<int> is_prime(n + 1, true);
  std::vector<int> res;
  for (int i = 2; i <= n; i++) {
    if (is_prime[i]) {
      res.push_back(i);
      for (int j = i * 2; j <= n; j += i) is_prime[j] = false;
    }
  }
  return res;
}

// 素因数分解
std::map<int, int> prime_factor(int n) {
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

// 繰り返し二乗法


// セグメント木: RMQ(Range Minimum Query)
// 区間に対する演算を、各サブ区間の演算結果をキャッシュすることで高速に行う


// Binary Indexed Tree

// Ford-Fulkderson

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

// テスト用main関数
int main() {

}
