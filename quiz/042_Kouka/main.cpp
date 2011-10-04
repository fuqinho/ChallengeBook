#include <iostream>
#include <vector>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)

int main() {
    const int VALUE[] = {1, 5, 10, 50, 100, 500};
    vector<int> C(sizeof(VALUE) / sizeof(VALUE[0]));
    REP(i, C.size()) cin >> C[i];
    int A;
    cin >> A;

    REP(i, C.size()) {
       int val = VALUE[C.size() - 1 - i];
       int count = C[C.size() - 1 - i];
       int usedNum = min(A / val, count);
       cout << val << ": " << usedNum << "枚" << endl;
       A -= val * usedNum;
    }
}

