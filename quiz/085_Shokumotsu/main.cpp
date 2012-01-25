#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
#define dump(x)  cerr << #x << " = " << (x) << endl;

class UnionFindTree {
public:
    UnionFindTree(int n) {
        par = vector<int>(n);
        rank = vector<int>(n);
        for (int i = 0; i < n; i++) par[i] = i;
    }
    int find(int x) {
        if (par[x] == x) return x;
        else return par[x] = find(par[x]);
    }
    void unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if (x != y)
            if (rank[rx] < rank[ry]) par[rx] = ry;
            else {
                par[ry] = rx;
                if (rank[rx] == rank[ry]) rank[rx]++;
            }
        par[ry] = rx;
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
private:
    vector<int> par;
    vector<int> rank;
};

int id(int index, int type) {
    return index * 3 + type;
}

int solve(int N, vector<int>& vt, vector<int>& vx, vector<int>& vy) {
    int errors = 0;
    UnionFindTree tree(N * 3);
    for (int i = 0; i < vt.size(); i++) {
        if (vx[i] < 0 || vx[i] >= N || vy[i] < 0 || vy[i] >= N) {
            cerr << "case #" << i << " violates consistency" << endl; 
            errors++;
        } else {
            if (vt[i] == 1) {
                if (tree.same(id(vx[i],0), id(vy[i],1)) || tree.same(id(vx[i],0), id(vy[i],2))) {
                    cerr << "case #" << i << " violates consistency" << endl; 
                    errors++;
                } else {
                    tree.unite(id(vx[i], 0), id(vy[i], 0));
                    tree.unite(id(vx[i], 1), id(vy[i], 1));
                    tree.unite(id(vx[i], 2), id(vy[i], 2));
                }
            } else if (vt[i] == 2) {
                if (tree.same(id(vx[i],0), id(vy[i],0)) || tree.same(id(vx[i],0), id(vy[i],2))) {
                    cerr << "case #" << i << " violates consistency" << endl; 
                    errors++;
                } else {
                    tree.unite(id(vx[i], 0), id(vy[i], 1));
                    tree.unite(id(vx[i], 1), id(vy[i], 2));
                    tree.unite(id(vx[i], 2), id(vy[i], 0));
                }
            }
        }
    }
    return errors;
}

int main() {
    int N, K;
    cin >> N >> K;
    vector<int> vt, vx, vy;
    for (int i = 0; i < K; i++) {
        int type, x, y;
        cin >> type >> x >> y;
        vt.push_back(type);
        vx.push_back(x-1);
        vy.push_back(y-1);
    }

    int answer = solve(N, vt, vx, vy);
    cout << answer << endl;
}

