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
        rank = vector<int>(n, 0);
        for (int i = 0; i < n; i++) par[i] = i;
    }
    int find(int x) {
        if (x == par[x]) return x;
        else return par[x] = find(par[x]);
    }
    void unite(int x, int y) {
        int rx = find(x);
        int ry = find(y);
        if (rx != ry) {
            if (rank[rx] < rank[ry]) {
                par[rx] = ry;
            } else {
                par[ry] = rx;
                if (rank[rx] == rank[ry]) rank[rx]++;
            }
        }
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
private:
    vector<int> par;
    vector<int> rank;
};

struct edge {int from, to, cost;};
bool operator<(const edge& l, const edge& r) { return l.cost < r.cost; }

int kruskal(int V, vector<edge>& es) {
    sort(es.begin(), es.end());
    UnionFindTree tree(V);
    int res = 0;
    for (int i = 0; i < es.size(); i++) {
        if (!tree.same(es[i].from, es[i].to)) {
            tree.unite(es[i].from, es[i].to);
            res += es[i].cost;
        }
    }
    return res;
}

int main() {
    int N, M, R;
    cin >> N >> M >> R;

    int V = N + M;
    int E = R;
    vector<edge> es(R);

    for (int i = 0; i < R; i++) {
        int x, y, d;
        cin >> x >> y >> d;
        es[i] = (edge){x, N+y, -d};
    }

    int krusRes = kruskal(V, es);
    cout << krusRes << endl;
    cout << "Answer: " << 10000 * V + krusRes << endl;
}

