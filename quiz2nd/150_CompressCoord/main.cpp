#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <iomanip>
#include <cmath>
#include <cstdio>
#include <string>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<string> VS;
typedef pair<int, int> PII;
typedef long long LL;
#define ALL(a)  (a).begin(),(a).end()
#define RALL(a) (a).rbegin(), (a).rend()
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
const double EPS = 1e-10;
const double PI  = acos(-1.0);
#define dump(x)  cerr << #x << " = " << (x) << endl;
#define debug(x) cerr << #x << " = " << (x) << " (L" << __LINE__ << ")" << " " << __FILE__ << endl;
#define check(x) cerr << #x << " = "; REP(q,(x).size()) cerr << (x)[q] << " "; cerr << endl;
#define checkn(x,n) cerr << #x << " = "; for(int i=0;i<(x).size()&&i<(n);++i) cerr << (x)[i] << " "; cerr << endl;

int compress(VI& X1, VI& X2, int w) {
  int n = X1.size();
  REP(i, n) {
    if (X1[i] > X2[i]) swap(X1[i], X2[i]);
  }

  vector<int> separators;
  REP(i, X1.size()) {
    separators.push_back(X1[i]-1);
    if (X2[i] != w) separators.push_back(X2[i]);
  }
  sort(ALL(separators));
  separators.erase(unique(ALL(separators)), separators.end());
  check(separators);

  REP(i, X2.size()) {
    X1[i] = find(ALL(separators), X1[i]-1) - separators.begin();
    X2[i] = find(ALL(separators), X2[i]) - separators.begin() - 1;
  }
  check(X1);
  check(X2);
  return separators.size();
}

void print(VVI& tile) {
  cerr << "----------------" << endl;
  for (int i = 0; i < tile.size(); i++) {
    for (int j = 0; j < tile[i].size(); j++) {
      if (tile[i][j] == -1) {
        cout << "*";
      } else {
        cout << tile[i][j];
      }
    }
    cout << endl;
  }
}

void fill(VVI& tile, int i, int j, int id) {
  static const int dr[] = {0, 0, -1, 1};
  static const int dc[] = {-1, 1, 0, 0};
  tile[i][j] = id;
  queue<PII> que;
  que.push(make_pair(i, j));
  while (!que.empty()) {
    PII p = que.front(); que.pop();
    REP(i, 4) {
      int nr = p.first + dr[i];
      int nc = p.second + dc[i];
      if (nr >= 0 && nr < tile.size() && nc >= 0 && nc < tile[0].size()) {
        if (tile[nr][nc] == 0) {
          tile[nr][nc] = id;
          que.push(make_pair(nr, nc));
        }
      }
    }
  }
}

int getAreaCount(VVI& tile) {
  int id = 1;
  int res = 0;
  for (int i = 0; i < tile.size(); i++) {
    for (int j = 0; j < tile[0].size(); j++) {
      if (tile[i][j] == 0) {
        fill(tile, i, j, id);
        res++;
        id++;
      }
    }
  }
  print(tile);
  
  return res;
}

int solve(int W, int H, int N, VI& X1, VI& X2, VI& Y1, VI& Y2) {
  W = compress(X1, X2, W);
  H = compress(Y1, Y2, H);
  debug(W);
  debug(H);

  VVI tile(H, VI(W, 0));
  REP(i, N) {
    if (X1[i] == X2[i]) {
      for (int y = min(Y1[i], Y2[i]); y <= max(Y1[i], Y2[i]); y++) {
        tile[y][X1[i]] = -1;
      }
    } else {
      for (int x = min(X1[i], X2[i]); x <= max(X1[i], X2[i]); x++) {
        tile[Y1[i]][x] = -1;
      }
    }
  }

  print(tile);
  
  /*
  REP(i, H) {
    REP(j, W) cout << tile[i][j];
    cout << endl;
  }
  */

  return getAreaCount(tile);
}

int main() {
  int W, H, N;
  cin >> W >> H >> N;
  vector<int> X1(N), X2(N), Y1(N), Y2(N);
  REP(i, N) {
    cin >> X1[i] >> X2[i] >> Y1[i] >> Y2[i];
  }
  int answer = solve(W, H, N, X1, X2, Y1, Y2);
  cout << answer << endl;
}

