
#include <set>
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
    int n, m, k ,c;
    cin >> n >> m >> k >> c;

    vector<vector<int>> happiness(n + 1, vector<int>(m + 1, -1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> happiness[i][j];
        }
    }

    vector<pair<int, int>> friendships;
    friendships.reserve(k);
    for (int i = 0; i < k; i++) {
        int u, v;
        cin >> u >> v;
        friendships.push_back({u, v});
    }
    
    static int BIG = 1e6;
    static int S = n + n*m + 1;
    static int T = S + 1;
    FlowNetwork net = FlowNetwork(T + 1);

    for (int hippo = 1; hippo <= n; hippo++) {
        int prev = (hippo - 1) * (m + 1);
        net.add_edge(S, prev, net.INF);
        for (int pond = 1; pond <= m; pond++) {
            net.add_edge(
                prev,
                (hippo - 1) * (m + 1) + pond,
                BIG - (long long)happiness[hippo][pond]
            );
            net.add_edge(
                (hippo - 1) * (m + 1) + pond,
                prev,
                net.INF
            );
            prev = (hippo - 1) * (m + 1) + pond;
        }
        net.add_edge(prev, T, net.INF);
    }
    
    for (auto friendship: friendships) {
        for (int pond = 1; pond <= m; pond++) {
            int pond1 = (friendship.first - 1) * (m + 1) + pond;
            int pond2 = (friendship.second - 1) * (m + 1) + pond;
            net.add_edge(pond1, pond2, c);
            net.add_edge(pond2, pond1, c);
        }
    }

    long long min_cut = net.dinic(S, T);

    cout << n * BIG - min_cut << '\n';
}

