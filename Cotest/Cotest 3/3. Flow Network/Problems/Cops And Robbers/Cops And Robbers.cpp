
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
    int n, m, c;
    cin >> n >> m >> c;

    pair<int, int> bank = {-1, -1};

    vector<string> grid(m, "");
    for (int i = 0; i < m; i++) {
        cin >> grid[i];
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 'B') {
                bank = {i, j};
            }
        }
    }

    vector<int> costs(c, -1);
    for (int i = 0; i < c; i++) {
        cin >> costs[i];
    }

    auto convert = [&] (int r, int c) -> int {
        return r * n + c;
    };

    // bank                 -> s
    // [0, n*m - 1]         -> grid cell in
    // [n*m, 2*n*m - 1]     -> grid cell out
    // [2*n*m]              -> t
    const int IN_BASE = 0;
    const int OUT_BASE = n * m;
    const int T = 2 * n * m;
    const int S = IN_BASE + convert(bank.first, bank.second);
    FlowNetwork network = FlowNetwork(2*n*m + 1);

    const int di[4] = {0, 0, 1, -1};
    const int dj[4] = {1, -1, 0, 0};

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int curr = convert(i, j);
            auto value = grid[i][j];
            if (value == '.' || value == 'B') {
                network.add_edge(IN_BASE + curr, OUT_BASE + curr, network.INF);
            } else {
                network.add_edge(IN_BASE + curr, OUT_BASE + curr, costs[value-'a']);
            }
            for (int k = 0; k < 4; k++) {
                int next_i = i + di[k];
                int next_j = j + dj[k];
                if (0 <= next_i && next_i < m && 0 <= next_j && next_j < n) {
                    int next = convert(next_i, next_j);
                    network.add_edge(OUT_BASE + curr, IN_BASE + next, network.INF);
                } else {
                    network.add_edge(OUT_BASE + curr, T, network.INF);
                }
            }
        }
    }

    long long min_cut = network.dinic(S, T);

    if (min_cut >= network.INF) {
        cout << -1 << '\n';
    } else {
        cout << min_cut << '\n';
    }
}