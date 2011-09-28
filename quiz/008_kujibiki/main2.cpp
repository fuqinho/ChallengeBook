#include <iostream>
#include <vector>
using namespace std;

string solve(int N, int M, vector<int>& K) {
    vector<int> pair_totals;
    for (int i = 0; i < K.size(); i++)
        for (int j = 0; j < K.size(); j++)
            pair_totals.push_back(K[i] + K[j]);
    sort(pair_totals.begin(), pair_totals.end());

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
