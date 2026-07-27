
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
    int n;
    cin >> n;

    vector<string> grid(n, "");
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    static int di[4] = {0, 1, -1, 0};
    static int dj[4] = {1, 0, 0, -1};

    static int S = n*n;
    static int T = n*n + 1;
    FlowNetwork network = FlowNetwork(n*n + 2);

    auto convert = [&] (int r, int c) -> int {
        return r * n + c;
    };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == '#') {
                int curr = convert(i, j);
                if (i % 2 == j % 2) {
                    network.add_edge(S, curr, 1);
                    for (int k = 0; k < 4; k++) {
                        int next_i = i + di[k];
                        int next_j = j + dj[k];
                        if (0 <= next_i && next_i < n && 0 <= next_j && next_j < n) {
                            if (grid[next_i][next_j] == '#') {
                                int next = convert(next_i, next_j);
                                network.add_edge(curr, next, 1);
                            }
                        }
                    }
                } else {
                    network.add_edge(curr, T, 1);
                }
            }
        }
    }

    long long max_flow = network.dinic(S, T);

    cout << max_flow << '\n';
}