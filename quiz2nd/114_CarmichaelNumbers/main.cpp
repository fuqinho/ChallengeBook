#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
#define dump(x)  cerr << #x << " = " << (x) << endl;

typedef long long ll;

ll mod_pow(ll x, ll n, ll mod) {
    ll res = 1;
    while (n > 0) {
        if (n & 1) res = res * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return res;
}

bool is_prime(int n) {
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

bool carmichael(int n) {
    if (is_prime(n)) return false;
    for (int x = 2; x < n; x++) {
        if (mod_pow(x, n, n) != mod_pow(x, 1, n)) return false;
    }
    return true;
}

int main() {
    dump(carmichael(17));
    dump(carmichael(561));
    dump(carmichael(4));
}

