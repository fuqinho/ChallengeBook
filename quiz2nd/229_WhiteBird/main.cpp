#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#define debug(x) cerr << #x << " = " << (x) << " (L" << __LINE__ << ")" << " " << __FILE__ << endl;

static const double EPS = 1e-10;
static const int MAX_N = 50;
static const double G = 9.8;

int N;
double V, X, Y;
double L[MAX_N], B[MAX_N], R[MAX_N], T[MAX_N];

double calc(double vy, double t) {
  return vy * t - 0.5 * G * t * t;
}

int cmp(double a, double b, double x) {
  if (x < a + EPS) return -1;
  if (x > b - EPS) return 1;
  return 0;
}

bool check(double tx, double ty) {
  double a = (1.0 / 4.0) * G * G;
  double b = G * ty - V * V;
  double c = tx * tx + ty * ty;

  double D = b * b - 4.0 * a * c;
  if (fabs(D) <= EPS) D = 0.0;
  if (D < 0) return false;
  for (int d = -1; d <= 1; d+=2) {
    double t_squared = (-b + d * sqrt(D)) / (2.0 * a);
    if (t_squared <= 0) continue;

    // calc initial velocity to hit (tx, ty)
    double t = sqrt(t_squared);
    double vx = tx / t;
    double vy = (ty + 0.5 * G * t * t) / t;

    // check if the course is beyond pig
    double py = calc(vy, X / vx);
    if (py < Y - EPS) continue;

    // check if the course is clear
    bool isClear = true;
    for (int i = 0; i < N; i++) {
      if (L[i] >= X) continue;
      if (R[i] >= X && T[i] >= Y && B[i] <= py) {
        isClear = false;
        break;
      }
      double ly = calc(vy, L[i] / vx);
      double ry = calc(vy, R[i] / vx);
      int posL = cmp(B[i], T[i], ly);
      int posR = cmp(B[i], T[i], ry);
      if (posL * posR <= 0) {
        isClear = false;
        break;
      }

      double ht = vy / G;
      int posX_high = cmp(L[i], R[i], vx * ht);
      double hy = calc(vy, ht);
      int posH = cmp(B[i], T[i], hy);
      if (posX_high == 0 && posH >= 0 && posL < 0) {
        isClear = false;
        break;
      }
    }
    if (isClear) return true;
  }
  return false;
}

bool solve() {
  for (int i = 0; i < N; i++) {
    R[i] = min(R[i], X);
  }
  if (check(X, Y)) return true;
  for (int i = 0; i < N; i++) {
    if (check(L[i], T[i]) || check(R[i], T[i])) return true;
  }
  return false;
}

int main() {
  cin >> N >> V >> X >> Y;
  for (int i = 0; i < N; i++) {
    cin >> L[i] >> B[i] >> R[i] >> T[i];
  }

  bool isOK = solve();
  cout << (isOK ? "Yes" : "No") << endl;
}
