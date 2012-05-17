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


vector<double> gauss_jordan(const vector<vector<double> >& A, const vector<double>& b) {
  int n = A.size();
  vector<vector<double> > B(n, vector<double>(n+1));
  REP(i, n) REP(j, n) B[i][j] = A[i][j];
  REP(i, n) B[i][n] = b[i];

  /*
  REP(i, B.size()) {
    REP(j, B[i].size()) printf("%.1f ", B[i][j]);
    printf("\n");
  }
  */

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


int main() {
  int N, M;
  cin >> N >> M;
  vector<string> area(N);
  REP(i, N) cin >> area[i];

  int n = N*M;
  vector<vector<double> > A(n, vector<double>(n, 0));
  vector<double> b(n, 0);

  REP(i, N) {
    REP(j, M) {
      if (i == N-1 && j == M-1) continue;

      int idx = i * M + j;
      A[idx][idx] = 1;
      int count = 0;
      if (area[i][j] == '#') {
        b[idx] = 0;
      } else {
        static const int dx[] = {-1, 1, 0, 0};
        static const int dy[] = {0, 0, -1, 1};
        REP(k, 4) {
          int y = i + dy[k];
          int x = j + dx[k];
          if (x >= 0 && x < M && y >= 0 && y < N && area[y][x] != '#') count++;
        }
        double rate = -1.0 / count;
        REP(k, 4) {
          int y = i + dy[k];
          int x = j + dx[k];
          if (x >= 0 && x < M && y >= 0 && y < N && area[y][x] != '#') {
            int idx2 = y * M + x;
            //cerr << "A[" << idx << "][" << idx2 << "]" << endl;
            A[idx][idx2] = rate;
          }
        }
        A[idx][idx] = 1;
        b[idx] = 1;
      }
    }
  }
  A[n-1][n-1] = 1;
  b[n-1] = 0;

  vector<double> ans = gauss_jordan(A, b);
  if (ans.size() > 0) {
    cout << ans[0] << endl;
  } else {
    cout << "not found" << endl;
  }

  REP(i, N) {
    REP(j, M) {
      printf("%04d ", (int)ans[i*M+j]);
    }
    cerr << endl;
  }
}

