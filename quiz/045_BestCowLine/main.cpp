#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
#define dump(x)  cerr << #x << " = " << (x) << endl;

int main() {
    string s;
    cin >> s;
    
    cerr << "input: " << s << endl;
    int front = 0;
    int tail = s.size() - 1;
    while (front <= tail) {
        int f = front, t = tail;
        bool takeLeft = false;
        for (int i = front; i <= tail; i++) {
            if (s[i] < s[tail-(i-front)]) {
                takeLeft = true;
                break;
            } else if (s[i] > s[tail-(i-front)]) {
                break;
            }
        }
        if (takeLeft) {
            cout << s[front];
            front++;
        } else {
            cout << s[tail];
            tail--;
        }
    }
    cout << endl;
}

