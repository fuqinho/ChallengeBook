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
#include <string>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<string> VS;
typedef pair<int, int> PII;
typedef long long LL;
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
const double EPS = 1e-10;
const double PI  = acos(-1.0);
#define dump(x)  cerr << #x << " = " << (x) << endl;
#define debug(x) cerr << #x << " = " << (x) << " (L" << __LINE__ << ")" << " " << __FILE__ << endl;

int n = 5;
int a[] = {2, 3, 3 ,5, 6};
int k = 3;

int main() {
  vector<int> A(n);
  REP(i, n) A[i] = a[i];

  /*
  vector<int>::iterator it = lower_bound(A.begin(), A.end(), k);
  cout << (it - A.begin()) << endl;
  */

  int lower = -1;
  int upper = n;
  while (upper - lower > 1) {
    int mid = (lower + upper) / 2;
    if (A[mid] >= k) {
      upper = mid;
    } else {
      lower = mid;
    }
  }
  cout << upper << endl;
}

