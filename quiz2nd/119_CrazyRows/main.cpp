#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
#define dump(x)  cerr << #x << " = " << (x) << endl;

int solve(vector<string>& matrix) {
    vector<int> c(matrix.size());
    REP(i, matrix.size()) {
        int x = 0;
        REP(j, matrix[i].size()) if (matrix[i][j] == '1') x = j+1;
        c[i] = x;
    }

    REP(i, c.size()) cerr << c[i] << " ";
    cerr << endl;

    int ans = 0;
    REP(i, c.size()) {
        if (c[i] > i + 1) {
            for (int j = i + 1; j < c.size(); j++) {
                if (c[j] <= i + 1) {
                    cerr << "-- " << j << " -> " << i << endl;
                    for (int k = j - 1; k >= i; k--) {
                        swap(c[k], c[k+1]);
                        ans++;
                        for (int l = 0; l < c.size(); l++) cerr << c[l] << " "; cerr << endl;
                    }
                    break;
                }
            }
            cerr << endl;
        }
    }
    return ans;
}

int main() {
    int n; cin >> n;
    vector<string> matrix(n);
    REP(i, n) cin >> matrix[i];

    int answer = solve(matrix);
    cout << "Answer: " << answer << endl;
}

