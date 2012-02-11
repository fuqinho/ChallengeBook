#include <iostream>
#include <vector>
using namespace std;

struct {
    vector<vertex*> edge;
};
vertex G[10];

int main() {
    int V, E;
    cin >> V >> E;
    
    vector<vector<int> > G(V, vector<int>());
    for (int i = 0; i < E; i++) {
        int s, t;
        cin >> s >> t;
        //G[s].push_back(t);
        G[s].edge.push_back(&G[t]);
    }
}
