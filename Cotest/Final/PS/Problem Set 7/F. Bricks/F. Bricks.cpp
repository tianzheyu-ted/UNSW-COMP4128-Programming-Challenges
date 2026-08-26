
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

// d[0], d[1]: Horizontal direction
// d[2], d[3]: Vertical direction
static int di[2] = {0, 1};
static int dj[2] = {1, 0};

int main() {
    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> blacks;
    blacks.reserve(n*m);

    vector<string> grid(n, "");
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    int counter = 0;

    // { NodeID, Is_Horizontal }
    vector<vector<vector<pair<int, bool>>>> adj(
        n, vector<vector<pair<int, bool>>>(m, vector<pair<int, bool>>(2, {-1, false}))
    );

    map<pair<int, int>, int> black_map;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '#') {
                black_map[{i, j}] = blacks.size();
                blacks.push_back({i, j});
                for (int k = 0; k < 2; k++) {
                    int next_i = i + di[k];
                    int next_j = j + dj[k];
                    if (0 <= next_i && next_i < n && 0 <= next_j && next_j < m) {
                        if (grid[next_i][next_j] == '#') {
                            adj[i][j][k] = {counter, (k == 0)};
                            counter++;
                        }
                    }
                }
            }
        }
    }

    static int BLACK_CELL_BASE = blacks.size();
    static int ADJ_BASE = BLACK_CELL_BASE + counter;
    static int S = ADJ_BASE;
    static int T = S + 1;

    FlowNetwork network = FlowNetwork(T + 1);

    // for (int i = 0; i < BLACK_CELL_BASE; i++) {
    //     network.add_edge(S, i, 1);
    // }

    for (auto black : blacks) {
        for (auto next : adj[black.first][black.second]) {
            if (next.first != -1) {
                int edge_node = BLACK_CELL_BASE + next.first;
                if (next.second) {
                    // Horizontal: S --1--> edge_node --inf--> blacks
                    network.add_edge(S, edge_node, 1);
                    network.add_edge(edge_node, black_map[black], network.INF);
                    network.add_edge(
                        edge_node,
                        black_map[{black.first, black.second + 1}],
                        network.INF
                    );
                } else {
                    // Vertical: blacks --inf--> edge_node --1--> T
                    network.add_edge(black_map[black], edge_node, network.INF);
                    network.add_edge(
                        black_map[{black.first + 1, black.second}],
                        edge_node,
                        network.INF
                    );
                    network.add_edge(edge_node, T, 1);
                }
            }
        }
    }

    long long max_flow = network.dinic(S, T);
    cout << blacks.size() - (counter - max_flow) << '\n';
}