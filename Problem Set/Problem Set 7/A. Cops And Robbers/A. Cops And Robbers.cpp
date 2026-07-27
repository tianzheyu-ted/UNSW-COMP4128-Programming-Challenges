
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
    int n, m, c;
    cin >> n >> m >> c;

    vector<string> grid(m);
    for (int i = 0; i < m; i++) {
        cin >> grid[i];
    }

    vector<int> cost(c);
    for (int i = 0; i < c; i++) {
        cin >> cost[i];
    }

    const int INF = 1e9;

    int S = -1;
    int T = 2 * m * n;

    auto get_in = [&](int r, int col) { return 2 * (r * n + col); };
    auto get_out = [&](int r, int col) { return 2 * (r * n + col) + 1; };

    FlowNetwork network = FlowNetwork(2 * n * m + 1);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            char ch = grid[i][j];

            int in = get_in(i, j);
            int out = get_out(i, j);

            if (ch == 'B') {
                network.add_edge(in, out, INF);
                S = out;
            } else if (ch == '.') {
                network.add_edge(in, out, INF);
            } else if (ch >= 'a' && ch <= 'z') {
                network.add_edge(in, out, cost[ch - 'a']);
            }

            if (i == 0 || j == 0 || i == m - 1 || j == n - 1) {
                network.add_edge(out, T, INF);
            }

            int di[] = {0, 0, 1, -1};
            int dj[] = {1, -1, 0, 0};
            for (int k = 0; k < 4; k++) {
                int next_i = i + di[k];
                int next_j = j + dj[k];
                if (0 <= next_i && next_i < m && 0 <= next_j && next_j < n) {
                    network.add_edge(out, get_in(next_i, next_j), INF);
                }
            }
        }
    }

    int max_flow = network.dinic(S, T);

    if (max_flow >= INF) {
        cout << -1 << '\n';
    } else {
        cout << max_flow << '\n';
    }

    return 0;
}