#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
#define dump(x)  cerr << #x << " = " << (x) << endl;

static const int INF = 999;

int N = 4;
struct Edge {
    int from, to, cost;
    Edge(int f, int t, int c) : from(f), to(t), cost(c) {}
};

int main() {
    vector<Edge> edges;
    // 0,1,2,3の順に並ぶ制約を表現する辺
    edges.push_back(Edge(1, 0, 0));
    edges.push_back(Edge(2, 1, 0));
    edges.push_back(Edge(3, 2, 0));
    // 仲の良い牛の制約を表現する辺
    edges.push_back(Edge(0, 2, 10));
    edges.push_back(Edge(1, 3, 20));
    // 仲が悪い牛の制約を表現する辺
    edges.push_back(Edge(2, 1, -3));

    // 求めたいのは、d[N-1] - d[0]の最大値
    // つまり、0からN-1への最短経路
    // このグラフの0からN-1への最短経路を求めると、
    // その最短経路が全ての制約を満たすもののうち距離が最大になる。
    // 負の辺を含むのでBellman-Fordを使う
    vector<int> d(N, INF);
    d[0] = 0;
    for (int i = 0; i < N; i++) {
        bool update = false;
        for (int j = 0; j < edges.size(); j++) {
            Edge& e = edges[j];
            if (d[e.from] != INF && d[e.to] > d[e.from] + e.cost) {
                d[e.to] = d[e.from] + e.cost;
                update = true;
            }
        }
        if (!update) break;
    }
    
    for (int i = 0; i < N; i++) cout << d[i] << " ";
}

