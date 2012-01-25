#include <iostream>
#include <queue>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
#define dump(x)  cerr << #x << " = " << (x) << endl;

int N = 3;
int L[] = {8, 5, 8};

int main() {
    priority_queue<int, vector<int>, greater<int> > q;
    for (int i = 0; i < N; ++i) q.push(L[i]);
    int cost = 0;
    while (q.size() > 1) {
        int t1 = q.top(); q.pop();
        int t2 = q.top(); q.pop();
        cost += t1 + t2;
        q.push(t1 + t2);
    }
    cout << cost << endl;
}

