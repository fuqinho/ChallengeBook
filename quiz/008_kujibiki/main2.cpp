#include <iostream>
#include <vector>
using namespace std;

string solve(int N, int M, vector<int>& K) {
    // 2つのくじを引いた合計の数を列挙する
    vector<int> pair_totals;
    for (int i = 0; i < K.size(); i++)
        for (int j = 0; j < K.size(); j++)
            pair_totals.push_back(K[i] + K[j]);

    // 二分探索のためにソートする
    sort(pair_totals.begin(), pair_totals.end());

    // pair_totalsの中身から2つの数を取り出してMになれば良い。
    // １つ取り出して、M-その数を二分探索で探す
    for (int i = 0; i < pair_totals.size(); i++)
        if (binary_search(pair_totals.begin(), pair_totals.end(),
                    M - pair_totals[i]))
            return "Yes";
    return "No";
}

int main() {
    
    // read problem from 
    int N, M, tmp;
    cin >> N >> M;
    vector<int> K;
    for (int i = 0; i < N; i++) {
        cin >> tmp;
        K.push_back(tmp);
    }

    // solve and print
    string result = solve(N, M, K);
    cout << result << endl;

    return 0;
}
