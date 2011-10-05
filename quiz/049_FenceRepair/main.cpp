#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
#define dump(x)  cerr << #x << " = " << (x) << endl;

int main() {
    int N;
    cin >> N;
    vector<int> L(N);
    REP(i, N) cin >> L[i];

    // 突っ込んだ整数の中から小さい順に値を取り出すためのpriority queueを作る
    // vectorで毎回sortしてもいいはず
    priority_queue<int, vector<int>, greater<int> > q;
    REP(i, N) q.push(L[i]);

    // 小さい値を2つ取り出して、合計をまた突っ込む操作を
    // 木が1枚になるまで繰り返す
    int result = 0;
    while (q.size() > 1) {
        int piece1 = q.top();
        q.pop();
        int piece2 = q.top();
        q.pop();
        int newPiece = piece1 + piece2;
        result += newPiece;
        q.push(newPiece);
    }
    cout << "Answer: " << result << endl;
}

