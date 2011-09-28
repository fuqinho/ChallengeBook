#include <iostream>
#include <vector>
using namespace std;

// startIndex以降で合計remainsになる和が作れるかチェックする
bool hasKSum(int startIndex, int remains, const vector<int>& A) {
    // 最後まで足してremainsが0なら成功
    if (startIndex == A.size())
        return remains == 0;

    // A[startIndex]を足した場合足さなかった場合どちらかで
    // 合計Kを作れればよい
    return hasKSum(startIndex + 1, remains, A) 
        || hasKSum(startIndex + 1, remains - A[startIndex], A);
}

int main() {
    // read input
    int N, K, tmp;
    vector<int> A;
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> tmp;
        A.push_back(tmp);
    }
    cin >> K;

    // 深さ優先探索を再帰関数で実行
    if (hasKSum(0, K, A))
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
}
