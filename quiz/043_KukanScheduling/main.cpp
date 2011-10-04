#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)

int main() {
    int N;
    cin >> N;
    vector<int> S(N);
    REP(i, N) cin >> S[i];
    vector<int> T(N);
    REP(i, N) cin >> T[i];

    vector< pair<int, int> > tasks;
    REP(i, N) tasks.push_back(pair<int, int>(T[i], S[i]));
    sort(tasks.begin(), tasks.end());
    
    vector< pair<int, int> >::iterator itr = tasks.begin();
    int curT = 0;
    int result = 0;
    while (itr != tasks.end()) {
        if ((*itr).second >= curT) {
            result++;
            curT = (*itr).first;
            cerr << "pick up task (s:" << (*itr).second << " t:" << (*itr).first << ")" << endl;
        }
        itr++;
    }
    cout << "Answer: " << result << endl;
}
