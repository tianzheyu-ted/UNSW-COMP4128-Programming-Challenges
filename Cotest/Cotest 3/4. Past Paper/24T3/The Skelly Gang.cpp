
#include <set>
#include <queue>
#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

struct DSU {
    vector<int> parent;
    DSU(int n) {
        parent.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i; 
        }
    }
    int find(int i) {
        if (parent[i] == i) {
            return i;
        }
        return parent[i] = find(parent[i]); 
    }
    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j; 
            return true; 
        }
        return false; 
    }
};

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
    vector <int> level, uptochild;

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

struct Edge {
    int from;
    int to;
    long long weight;
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<Edge> edges; edges.reserve(m);
    vector<vector<Edge>> adj(n + 1, vector<Edge>());
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        adj[a].push_back({a, b, c});
        adj[b].push_back({b, a, c});
        edges.push_back({a, b, c});
    }

    Edge target = edges[0];

    auto kruskal = [] (vector<vector<Edge>>& adj) -> pair<long long, set<tuple<int, int, long long>>> {
        int n = adj.size();
        struct KEdge { int u, v; long long w; };
        vector<KEdge> edges;
        for (int u = 0; u < n; ++u) {
            for (const auto& edge : adj[u]) {
                if (u < edge.to) {
                    edges.push_back({u, edge.to, edge.weight});
                }
            }
        }
        sort(edges.begin(), edges.end(), [](const KEdge& a, const KEdge& b) {
            return a.w < b.w;
        });
        DSU dsu(n);
        long long total_weight = 0;
        set<tuple<int, int, long long>> mst_edges;
        for (auto& e : edges) {
            if (dsu.unite(e.u, e.v)) {
                total_weight += e.w;
                mst_edges.insert({e.u, e.v, e.w});
            }
        }
        return {total_weight, mst_edges};
    };

    // auto [mst_weigth, mst] = kruskal(adj);

    // if (
    //     mst.count({target.from, target.to, target.weight})
    //     || mst.count({target.to, target.from, target.weight})
    // ) {
    //     cout << 0 << '\n';
    //     return 0;
    // }


    FlowNetwork net = FlowNetwork(n + 1);

    for (auto edge : edges) {
        if (edge.weight <= target.weight && !(edge.from == target.from && edge.to == target.to)) {
            net.add_edge(edge.from, edge.to, 1);
            net.add_edge(edge.to, edge.from, 1);
        }
    }
    
    long long max_flow = net.dinic(target.from, target.to);
    cout << max_flow << '\n';
}