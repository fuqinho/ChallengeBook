#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
#define dump(x)  cerr << #x << " = " << (x) << endl;

int main() {
    int N, R;
    cin >> N >> R;
    vector<int> X(N);
    REP(i, N) cin >> X[i];

    int veryLeft = X[0];
    int nextCenter = 0;
    int result = 1;
    REP(i, N) {
        cout << "check.. " << X[i] << endl;
        if (X[i] <= veryLeft + R) {
            nextCenter = i;
        } else {
            FOR(j, i, N) {
                if (X[j] > X[nextCenter] + R) {
                    cerr << X[j] << " is far from " << X[nextCenter] << endl;
                    veryLeft = X[j];
                    result++;
                    break;
                }
            }
        }
    }
    cout << "Result: " << result << endl;
}

