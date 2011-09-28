#include <iostream>
#include <vector>
using namespace std;

string solve(int N, int M, vector<int>& K) {
    for (int i = 0; i < K.size(); i++)
        for (int j = 0; j < K.size(); j++)
            for (int k = 0; k < K.size(); k++)
                for (int l = 0; l < K.size(); l++)
                    if (K[i] + K[j] + K[k] + K[l] == M)
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
