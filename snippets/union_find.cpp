#include <iostream>
#include <vector>
using namespace std;

class UnionFindTree {
public:
    UnionFindTree(int n) {
        par = vector<int>(n);
        rank = vector<int>(n);
        for (int i = 0; i < n; i++) par[i] = i;
    }

    // find root of x
    int find(int x) {
        if (par[x] == x)
            return x;
        else
            return par[x] = find(par[x]);
    }

    // xが属する集合とyが属する集合を併合
    void unite(int x, int y) {
        int rx = find(x);
        int ry = find(y);
        if (x != y) {
            if (rank[rx] < rank[ry]) {
                par[rx] = ry;
            } else {
                par[ry] = rx;
                if (rank[rx] == rank[ry]) {
                    rank[rx]++;
                }
            }
        }
        par[ry] = rx;
    }

    // xとyが同じ集合に属するかどうか
    bool same(int x, int y) {
        return find(x) == find(y);
    }

    void print() {
        cout << "\t";
        for (int i = 0; i < par.size(); i++) cout << i << " ";
        cout << endl;
        cout << "P:\t";
        for (int i = 0; i < par.size(); i++) {
            cout << par[i] << " ";
        }
        cout << endl;
        cout << "R:\t";
        for (int i = 0; i < par.size(); i++) {
            cout << rank[i] << " ";
        }
        cout << endl;
    }
    
private:
    vector<int> par;
    vector<int> rank;
};

int main() {
    UnionFindTree tree(10);

    tree.unite(2, 3);
    tree.unite(3, 8);
    tree.unite(6, 7);
    tree.print();
    cout << tree.same(3, 8) << endl;
    cout << tree.same(3, 7) << endl;
}

