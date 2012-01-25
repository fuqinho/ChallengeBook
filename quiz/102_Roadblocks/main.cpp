#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
#define dump(x)  cerr << #x << " = " << (x) << endl;

typedef pair<int, int> PII;
static const int INF = 999;

int N = 4;
int R = 4;
struct edge {
    int to, cost;
};

edge makeEdge(int to, int cost) {
    edge e;
    e.to = to;
    e.cost = cost;
    return e;
}

int main() {
    vector<vector<edge> > G(N);
    G[0].push_back(makeEdge(1, 100));
    G[1].push_back(makeEdge(0, 100));
    G[1].push_back(makeEdge(2, 250));
    G[2].push_back(makeEdge(1, 250));
    G[1].push_back(makeEdge(3, 200));
    G[3].push_back(makeEdge(1, 200));
    G[2].push_back(makeEdge(3, 100));
    G[3].push_back(makeEdge(2, 100));

    vector<int> dist(N, INF);
    vector<int> dist2(N, INF);

    priority_queue<PII, vector<PII>, greater<PII> > que;
    dist[0] = 0;
    que.push(PII(0, 0));

    while(!que.empty()) {
        PII p = que.top(); que.pop();
        int v = p.second;
        int d = p.first;
        if (d > dist2[v]) continue;
        for (int i = 0; i < G[v].size(); i++) {
            edge& e = G[v][i];
            int d2 = d + e.cost;
            if (dist[e.to] > d2) {
                swap(dist[e.to], d2);
                que.push(PII(dist[e.to], e.to));
            }
            if (dist2[e.to] > d2) {
                dist2[e.to] = d2;
                que.push(PII(dist2[e.to], e.to));
            }
        }
    }

    for (int i = 0; i < 4; i++) cout << dist[i] << " ";
    cout << endl;
    for (int i = 0; i < 4; i++) cout << dist2[i] << " ";
    cout << endl;
}

