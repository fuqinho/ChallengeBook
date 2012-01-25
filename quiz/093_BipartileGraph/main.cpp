#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)
#define dump(x)  cerr << #x << " = " << (x) << endl;

bool dfs(vector<vector<int> >& G, vector<int>& color, int v, int c) {
    color[v] = c;
    for (int i = 0; i < G[v].size(); i++) {
        if (color[G[v][i]] == c) return false;
        if (color[G[v][i]] == 0 && dfs(G, color, G[v][i], -c) == false) return false;
    }
    return true;
}

int main() {
    int V, E;
    cin >> V >> E;
    vector<vector<int> > G(V);
    vector<int> color(V);
    for (int i = 0; i < E; i++) {
        int s, t;
        cin >> s >> t;
        G[s].push_back(t);
        G[t].push_back(s);
    }

    int result = dfs(G, color, 0, 1);
    if (result) {
        for (int i = 0; i < color.size(); i++) cout << color[i] << " ";
        cout << endl;
    }
    cout << result << endl;
}

