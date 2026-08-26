
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

struct FlowNetwork {
    int n;
    const int INF = 1e9;
    vector<vector<long long>> adjMat, adjList ;

    // level [v] stores dist from s to v
    // uptochild [v] stores first non - useless child.
    vector <int > level, uptochild ;

    FlowNetwork (int _n): n(_n) {

    // adjacency matrix is zero - initialised
    adjMat.resize (n);

    for (int i = 0; i < n; i++) { adjMat [i]. resize (n); }
        adjList.resize (n);
        level.resize (n);
        uptochild.resize (n);
    }

    void add_edge (int u, int v, long long c) {
        // add to any existing edge without overwriting
        adjMat[u][v] += c;
        adjList[u]. push_back (v);
        adjList[v]. push_back (u);
    }

    void flow_edge (int u, int v, long long c) {
        adjMat[u][v] -= c;
        adjMat[v][u] += c;
    }

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue <int > q;
        q.push(s);
        level[s] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            uptochild [u] = 0; // reset uptochild
            for (int v : adjList [u]) {
                if (level[v] == -1 && adjMat[u][v] > 0) { // unseen and has capacity
                    level[v] = level[u] + 1;
                    q.push(v);
                }
            }
        }
        return level [t] != -1;
    }

    long long augment(int u, int t, long long f) {
        if (u == t) { return f; } // base case.
        // note the reference here! we increment uptochild[u], i.e. walk through u's neighbours
        // until we find a child that we can flow through
        for (int &i = uptochild[u]; i < adjList[u].size(); i++) {
            int v = adjList[u][i];
            // use only edges in the level graph with remaining capacity
            if (level[v] == level[u] + 1 && adjMat[u][v] > 0) {
                // revised flow is constrained also by this edge
                int rf = augment(v, t, min(f, (long long)adjMat[u][v]));
                // found a child we can flow through!
                if (rf > 0) {
                    flow_edge(u, v, rf);
                    return rf;
                }
            }
        }
        level[u] = -1;
        return 0;
    }

    long long dinic(int s, int t) {
        long long res = 0;
        while (bfs(s,t)) {
            while (long long x = augment(s, t, INF)) { res += x; }
            // when no further paths, find new level graph
        }
        return res;
    }
};


int main() {
    int n, m, k;
    cin >> n >> m >> k;

    // [0, n - 1]                   : hero_in
    // [n, 2*n - 1]                 : hero_out
    // [2*n, 2*n + m - 1]           : monster_in
    // [2*n + m, 2*n + 2*m - 1]     : monster_out
    // [2*n + 2*m]                  : potion
    // [2*n + 2*m + 1]              : S
    // [2*n + 2*m + 2]              : T    
    FlowNetwork network = FlowNetwork(2*n + 2*m + 3);

    // heroes -> monsters
    for (int i = 0; i < n; i++) {
        int t;
        cin >> t;
        for (int j = 0; j < t; j++) {
            int monster;
            cin >> monster;
            network.add_edge(n + i, 2*n + monster - 1, 1);
        }
    }

    // potion
    network.add_edge(2*n + 2*m + 1, 2*n + 2*m, k);

    // heroes 
    for (int i = 0; i < n; i++) {
        network.add_edge(i, i + n, 1);
        network.add_edge(2*n + 2*m + 1, i, network.INF);
        network.add_edge(2*n + 2*m, i + n, 1);
    }

    // monsters
    for (int i = 0; i < m; i++) {
        network.add_edge(2*n + i, 2*n + i + m, 1);
        network.add_edge(2*n + i + m, 2*n + 2*m + 2, network.INF);
    }

    long long max_flow = network.dinic(2*n + 2*m + 1, 2*n + 2*m + 2);

    cout << max_flow << '\n';
}