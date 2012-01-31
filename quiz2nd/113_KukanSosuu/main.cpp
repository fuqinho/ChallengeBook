#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
#define dump(x)  cerr << #x << " = " << (x) << endl;

int segment_sieve(long long a, long long b) {
    vector<int> is_prime_small((int)sqrt(b), true);
    vector<int> is_prime(b - a, true);
    for (int i = 2; (long long)i * i < b; i++) {
        if (is_prime_small[i]) {
            for (int j = 2 * i; (long long)j * j < b; j+= i) is_prime_small[j] = false;
            for (long long j = max(2LL, (a+i-1)/i) * i; j < b; j += i) is_prime[j - a] = false;
        }
    }
    return count(is_prime.begin(), is_prime.end(), true);
}

int main() {
    dump(segment_sieve(22, 37));
    dump(segment_sieve(22801763489, 22801787297));
}

