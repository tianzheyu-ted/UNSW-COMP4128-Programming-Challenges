
#include <map>
#include <queue>
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

struct FlowNetwork {
    struct Edge {
        int v;
        long long cap;
        long long flow;
        int rev;
    };

    int n;
    const int INF = 1e9;
    vector<vector<Edge>> adjList;

    // level [v] stores dist from s to v
    // uptochild [v] stores first non - useless child.
    vector <int> level, uptochild ;

    FlowNetwork(int _n): n(_n) {
        adjList.resize(n);
        level.resize(n);
        uptochild.resize(n);
    }

    void add_edge (int u, int v, long long c) {
        adjList[u].push_back({v, c, 0, (int)adjList[v].size()});
        adjList[v].push_back({u, 0, 0, (int)adjList[u].size() - 1});
    }

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        q.push(s);
        level[s] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            uptochild[u] = 0; 
            for (auto& edge : adjList[u]) {
                if (level[edge.v] == -1 && edge.cap - edge.flow > 0) { 
                    level[edge.v] = level[u] + 1;
                    q.push(edge.v);
                }
            }
        }
        return level[t] != -1;
    }

    long long augment(int u, int t, long long f) {
        if (u == t || f == 0) { return f; } 
        for (int &i = uptochild[u]; i < adjList[u].size(); i++) {
            Edge &edge = adjList[u][i];
            if (level[edge.v] == level[u] + 1 && edge.cap - edge.flow > 0) {
                long long rf = augment(edge.v, t, min(f, edge.cap - edge.flow));
                if (rf > 0) {
                    edge.flow += rf;
                    adjList[edge.v][edge.rev].flow -= rf;
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
        }
        return res;
    }
};

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    // [0, n - 1]       -> heroes
    // [n, n + m - 1]   -> monsters
    // [n + m]          -> potion
    // [n + m + 1]      -> S
    // [n + m + 2]      -> T

    static int HERO_IN_BASE = 0;
    static int HERO_OUT_BASE = n;
    static int MONSTER_BASE = 2 * n;
    static int POTION_IN = 2*n + m;
    static int POTION_OUT = 2*n + m + 1;
    static int S = 2*n + m + 2;
    static int T = 2*n + m + 3;

    FlowNetwork network = FlowNetwork(2*n + m + 4);

    // heros
    for (int i = 0; i < n; i++) {
        int t;
        cin >> t;
        for (int j = 0; j < t; j++) {
            int monster;
            cin >> monster;
            network.add_edge(HERO_OUT_BASE + i, MONSTER_BASE + monster - 1, 1);
        }
        network.add_edge(S, HERO_IN_BASE + i, network.INF);
        network.add_edge(HERO_IN_BASE + i, HERO_OUT_BASE + i, 1);
        network.add_edge(HERO_IN_BASE + i, POTION_IN, 1);
        network.add_edge(POTION_OUT, HERO_OUT_BASE + i, 1);
    }

    // monsters
    for (int i = 0; i < m; i++) {
        network.add_edge(MONSTER_BASE + i, T, 1);
    }
    
    // potion
    network.add_edge(POTION_IN, POTION_OUT, k);

    long long max_flow = network.dinic(S, T);

    cout << max_flow << '\n';
}