#include <iostream>
#include <vector>
#include <complex>
#include <cstdio>
#include <cmath>
using namespace std;

static const double EPS = 1e-10;
typedef complex<double> P;

double dot(const P& a, const P& b) {
  return a.real() * b.real() + a.imag() * b.imag();
}

double cross(const P& a, const P& b) {
  return a.real() * b.imag() - a.imag() * b.real();
}

bool isParallel(const P& a, const P& b) {
  return fabs(cross(a, b)) <= EPS;
}

// qが線分(p1, p2)上にあるかどうか
bool on_seg(const P& p1, const P& p2, const P& q) {
  return isParallel(p1-q, p2-q) && dot(p1-q, p2-q) <= 0;
}

// 直線(p1-p2)と直線(q1-q2)の交点
P intersection(const P& p1, const P& p2, const P& q1, const P& q2) {
  double t = cross(q2-q1, q1-p1) / cross(q2-q1, p2-p1);
  return p1 + (p2 - p1) * t; 
}

void solve(int N, vector<pair<P, P > >& s, vector<pair<int, int> >& q)
{
  vector<vector<bool> > connected(N, vector<bool>(N, false));
  for (int i = 0; i < N; i++) connected[i][i] = true;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (i != j) {
        bool c = false;
        if (isParallel(s[i].first - s[i].second, s[j].first - s[j].second)) {
          c = on_seg(s[i].first, s[i].second, s[j].first) ||
              on_seg(s[i].first, s[i].second, s[j].second) ||
              on_seg(s[j].first, s[j].second, s[i].first) ||
              on_seg(s[j].first, s[j].second, s[i].second);
        } else {
          P d = intersection(s[i].first, s[i].second, s[j].first, s[j].second);
          c = on_seg(s[i].first, s[i].second, d) && on_seg(s[j].first, s[j].second, d);
        }
        connected[i][j] = connected[j][i] = c;
      }
    }
  }

  for (int k = 0; k < N; k++) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        connected[i][j] = connected[i][j] || (connected[i][k] && connected[k][j]);
      }
    }
  }

  for (int i = 0; i < q.size(); i++) {
    cout << (connected[q[i].first][q[i].second] ? "CONNECTED" : "NOT CONNECTED") << endl;
  }
}

int main() {
  while (true) {
    int N; scanf("%d", &N);
    if (N == 0) break;

    vector<pair<P, P > > s(N);
    for (int i = 0; i < N; i++) {
      int a, b, c, d;
      scanf("%d %d %d %d", &a, &b, &c, &d);
      s[i].first = P(a, b);
      s[i].second = P(c, d);
    }
    vector<pair<int, int> > q;
    while (true) {
      int a, b; scanf("%d %d", &a, &b);
      if (a == 0 && b == 0) break;

      q.push_back(pair<int, int>(a-1, b-1));
    }

    solve(N, s, q);
  }
}

