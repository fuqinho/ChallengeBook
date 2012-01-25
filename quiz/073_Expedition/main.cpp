#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
#define dump(x)  cerr << #x << " = " << (x) << endl;

int N = 4, L = 25, P = 10;
int A[] = {10, 14, 20, 21};
int B[] = {10, 5, 2, 4};

int solve() {
    priority_queue<int> q;
    int fuel = P;
    int count = 0;
    for (int i = 0; i < N; i++) {
        while (fuel < A[i]) {
            if (q.empty()) return -1;
            fuel += q.top();
            q.pop();
            count++;
        }
        q.push(B[i]);
    }
    while (fuel < L) {
        if (q.empty()) return -1;
        fuel += q.top();
        q.pop();
        count++;
    }
    return  count;
}

int main() {
    cout << solve() << endl;
}

