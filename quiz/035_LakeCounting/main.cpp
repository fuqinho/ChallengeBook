#include <iostream>
#include <vector>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)

#define dump(x)  cerr << #x << " = " << (x) << endl;

int curLakeCount = '0';

void printGarden(vector<string>& garden) {
    REP(i, garden.size()) {
        REP(j, garden[i].size())
            cerr << garden[i][j];
        cerr << endl;
    }
}

void fillW(int r, int c, int N, int M, vector<string>& garden) {
    if (garden[r][c] == 'W') {
        garden[r][c] = curLakeCount;
        FOR(i, max(0, r-1), min(N, r+2))
            FOR(j, max(0, c-1), min(M, c+2))
                fillW(i, j, N, M, garden);
    }
}

int solve(int N, int M, vector<string>& garden) {
    int result = 0;
    REP(i, N) REP(j, M)
        if (garden[i][j] == 'W') {
            curLakeCount += 1;
            fillW(i, j, N, M, garden);
            result++;
        }
    return result;
}

int main() {
    int N, M;
    cin >> N >> M;
    vector<string> garden; 
    REP(t, N) {
        string t;
        cin >> t;
        garden.push_back(t);
    }
    cerr << "== Before ==" << endl;
    printGarden(garden);
    int answer = solve(N, M, garden);
    cerr << "== After ==" << endl;
    printGarden(garden);

    cout << "Answer: " << solve(N, M, garden) << endl;
}

