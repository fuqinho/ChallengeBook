#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int solve(vector<int>& A) {
    for (int i = 0; i < A.size(); i++) cerr << A[i] << " ";
    cerr << endl;

    int ans = 0;
    for (int i = 0; i < A.size(); i++)
        for (int j = 0; j < A.size(); j++)
            for (int k = 0; k < A.size(); k++)
                if (i != j && j != k && k != i)
                    if (A[i] + A[j] > A[k] && A[j] + A[k] > A[i] && A[k] + A[i] > A[j])
                        ans = max(ans, A[i] + A[j] + A[k]);

    return ans;
}

int main() {
    // read
    int N, tmp;
    vector<int> A;
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> tmp;
        A.push_back(tmp);
    }

    // solve and print
    int answer = solve(A);
    cout << answer << endl;

    return 0;
}

