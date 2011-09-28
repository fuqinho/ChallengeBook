#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int getMin(int L, int N, vector<int>& X) {
    int result = 0;
    for (int i = 0; i < X.size(); i++)
        result = max(result, min(X[i], L - X[i]));
    return result;
}

int getMax(int L, int N, vector<int>& X) {
    int result = 0;
    for (int i = 0; i < X.size(); i++)
        result = max(result, max(X[i], L - X[i]));
    return result;
}

int main() {
    int L, N, tmp;
    vector<int> X;
    cin >> L >> N;
    for (int i = 0; i < N; i++) {
        cin >> tmp;
        X.push_back(tmp);
    }

    cout << "min = " << getMin(L, N, X) << endl;
    cout << "max = " << getMax(L, N, X) << endl;

    return 0;
}
