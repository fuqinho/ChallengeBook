#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
#define dump(x)  cerr << #x << " = " << (x) << endl;

int prime_count(int n) {
    vector<bool> isPrime(n + 1, true);
    int res = 0;
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) res++;
        for (int j = i * 2; j <= n; j += i) isPrime[j] = false;
    }
    return res;
}

int main() {
    dump(prime_count(11));
    dump(prime_count(1000000));
}

