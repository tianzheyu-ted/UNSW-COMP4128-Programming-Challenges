
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

int main() {
    int n, r, s;
    cin >> n >> r >> s;

    int fertile_counter = 0;
    vector<string> garden(n, "");
    for (int i = 0; i < n; i++) {
        cin >> garden[i];
        for (int j = 0; j < n; j++) {
            if (garden[i][j] == '*') {
                fertile_counter++;
            }
        }
    }

    auto helper = [&] (int k) -> long long {
        static int ROW_BASE = 0;
        static int COL_BASE = n;
        static int S = 2 * n;
        static int T = 2 * n + 1;
        FlowNetwork net = FlowNetwork(T + 1);
        for (int i = 0; i < n; i++) {
            net.add_edge(S, ROW_BASE + i, k);
            net.add_edge(COL_BASE + i, T, k);
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (garden[i][j] == '*') {
                    net.add_edge(ROW_BASE + i, COL_BASE + j, 1);
                }
            }
        }
        return net.dinic(S, T);
    };

    long long min_cost = 1e18;
    for (int i = 0; i <= n; i++) {
        long long cost = i * s + (fertile_counter - helper(i)) * r;
        min_cost = min(cost, min_cost);
    }

    cout << min_cost << '\n';
}
