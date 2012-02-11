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

void flip(VVI& matrix, int i, int j) {
  static const int dr[] = {0, 0, 0, -1, 1};
  static const int dc[] = {0, 1, -1, 0, 0};
  REP(k, 5) {
    int r = i + dr[k];
    int c = j + dc[k];
    if (r >= 0 && r < matrix.size() && c >= 0 && c < matrix[0].size()) {
      matrix[r][c] = (matrix[r][c] == 1 ? 0 : 1);
    }
  }
}

bool solve(int M, int N, VVI& matrix, VVI& result) {
  VVI flippedMatrix = matrix;
  int minFlip = M * N + 1;
  // 一番上の行は全通り辞書順に試す
  VVI current = matrix;
  for (int mask = 0; mask < (1 << N); mask++) {
    int flipCount = 0;
    REP(i, M) REP(j, N) current[i][j] = matrix[i][j];
    REP(i, M) REP(j, N) flippedMatrix[i][j] = 0;

    // 一番上の行をひっくり返す
    for (int i = 0; i < N; i++) {
      if (mask & (1 << i)) {
        flip(current, 0, i);
        flippedMatrix[0][i] = 1;
        flipCount++;
      }
    }
    // そこから下は、一つ上のマスが1になってたらひっくり返す
    for (int i = 0; i < M - 1; i++) {
      for (int j = 0; j < N; j++) {
        if (current[i][j] == 1) {
          flip(current, i+1, j);
          flippedMatrix[i+1][j] = 1;
          flipCount++;
          /*
          cerr << "---------------" << endl;
          REP(i, M) {
            REP(j, N) cout << current[i][j] << " ";
            cout << "    ";
            REP(j, N) cout << result[i][j] << " ";
            cout << endl;
          }
          */
        }
      }
    }
    // 一番下の行が全部0になってたら成功
    bool success = true;
    for (int i = 0; i < N; i++) {
      if (current[M-1][i] == 1) {
        success = false;
        break;
      }
    }
    if (success) {
      if (minFlip > flipCount) {
        minFlip = flipCount;
        result = flippedMatrix;
      }
    }
  }

  return minFlip < M * N + 1;
}

int main() {
  int M, N;
  cin >> M >> N;
  VVI matrix(M, VI(N, 0));
  REP(i, M) REP(j, N) cin >> matrix[i][j];

  VVI result(M, VI(N, 0));
  bool success = solve(M, N, matrix, result);
  if (success) {
    REP(i, M) {
      REP(j, N) cout << result[i][j] << " ";
      cout << endl;
    }
  } else {
    cout << "IMPOSSIBLE" << endl;
  }
}

