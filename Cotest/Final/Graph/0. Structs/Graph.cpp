

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>
#include <cassert>

using namespace std;

const long long INF = 1e18;

struct DSU {
    vector<int> parent, size;
    DSU(int n) {
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
        size.assign(n, 1);
    }
    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }
    bool unite(int i, int j) {
        int root_i = find(i), root_j = find(j);
        if (root_i != root_j) {
            if (size[root_i] < size[root_j]) swap(root_i, root_j);
            parent[root_j] = root_i;
            size[root_i] += size[root_j];
            return true;
        }
        return false;
    }
};


// --- 万能图类 ---
class Graph {
public:
    struct Edge {
        int to;
        long long weight;
        long long cap;  // 网络流容量
        long long flow; // 网络流当前流量
        int rev;        // 反向边在邻接表中的索引
    };

    int n;
    bool is_directed;
    vector<vector<Edge>> adj;
    
    // 用于 LCA 的倍增数组
    int LOG;
    vector<vector<int>> up;
    vector<int> depth;

    Graph(int n, bool directed = false) : n(n), is_directed(directed), adj(n) {}

    // 添加普通边 (带权或无权)
    void add_edge(int u, int v, long long weight = 1) {
        adj[u].push_back({v, weight, 0, 0, -1});
        if (!is_directed) {
            adj[v].push_back({u, weight, 0, 0, -1});
        }
    }

    // 添加网络流边 (自带反向边残量网络)
    void add_flow_edge(int u, int v, long long capacity) {
        adj[u].push_back({v, 0, capacity, 0, (int)adj[v].size()});
        adj[v].push_back({u, 0, 0, 0, (int)adj[u].size() - 1});
    }

    // ==========================================
    // 1. 基础遍历 (DFS & BFS)
    // ==========================================
    vector<int> bfs(int start) {
        vector<int> dist(n, -1);
        queue<int> q;
        q.push(start);
        dist[start] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto& edge : adj[u]) {
                if (dist[edge.to] == -1) {
                    dist[edge.to] = dist[u] + 1;
                    q.push(edge.to);
                }
            }
        }
        return dist;
    }

    vector<bool> dfs(int start) {
        vector<bool> visited(n, false);
        auto dfsRec = [&] (int curr) {
            if (visited[curr]) {
                return visited;
            } else {
                visited[curr] = true;
                for (auto& edge : adj[curr]) {
                    dfs(edge.to);
                }
                return visited;
            }
        };
    }

    // ==========================================
    // 2. 桥和割点 (Tarjan Bridge Finding)
    // ==========================================
    vector<pair<int, int>> find_bridges() {
        vector<pair<int, int>> bridges;
        vector<int> tin(n, 0), low(n, 0);
        int timer = 0;
        auto dfs = [&](auto& self, int u, int p) -> void {
            tin[u] = low[u] = ++timer;
            for (auto& edge : adj[u]) {
                int v = edge.to;
                if (v == p) continue; // 过滤无向图直接回边
                if (tin[v]) {
                    low[u] = min(low[u], tin[v]);
                } else {
                    self(self, v, u);
                    low[u] = min(low[u], low[v]);
                    if (low[v] > tin[u]) bridges.push_back({u, v});
                }
            }
        };
        for (int i = 0; i < n; ++i) {
            if (!tin[i]) dfs(dfs, i, -1);
        }
        return bridges;
    }

    // ==========================================
    // 3. 拓扑排序 (Kahn's Algorithm)
    // ==========================================
    vector<int> topological_sort() {
        vector<int> in_degree(n, 0), order;
        for (int u = 0; u < n; ++u)
            for (auto& edge : adj[u]) in_degree[edge.to]++;
        queue<int> q;
        for (int i = 0; i < n; ++i)
            if (in_degree[i] == 0) q.push(i);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            order.push_back(u);
            for (auto& edge : adj[u])
                if (--in_degree[edge.to] == 0) q.push(edge.to);
        }
        if (order.size() < n) return {}; // 存在环
        return order;
    }

    // ==========================================
    // 4. 强连通分量 SCC (Tarjan)
    // ==========================================
    vector<vector<int>> tarjan_scc() {
        vector<vector<int>> sccs;
        vector<int> tin(n, 0), low(n, 0), scc_id(n, -1);
        vector<bool> in_stack(n, false);
        stack<int> st;
        int timer = 0;

        auto dfs = [&](auto& self, int u) -> void {
            tin[u] = low[u] = ++timer;
            st.push(u);
            in_stack[u] = true;
            for (auto& edge : adj[u]) {
                int v = edge.to;
                if (!tin[v]) {
                    self(self, v);
                    low[u] = min(low[u], low[v]);
                } else if (in_stack[v]) {
                    low[u] = min(low[u], tin[v]);
                }
            }
            if (low[u] == tin[u]) {
                vector<int> component;
                while (true) {
                    int v = st.top(); st.pop();
                    in_stack[v] = false;
                    component.push_back(v);
                    if (u == v) break;
                }
                sccs.push_back(component);
            }
        };
        for (int i = 0; i < n; ++i)
            if (!tin[i]) dfs(dfs, i);
        return sccs;
    }

    // ==========================================
    // 5. 最小生成树 MST (Kruskal)
    // ==========================================
    pair<long long, vector<pair<int, int>>> kruskal() {
        struct KEdge { int u, v; long long w; };
        vector<KEdge> edges;
        for (int u = 0; u < n; ++u)
            for (auto& edge : adj[u])
                if (u < edge.to) edges.push_back({u, edge.to, edge.weight});
        
        sort(edges.begin(), edges.end(), [](const KEdge& a, const KEdge& b) {
            return a.w < b.w;
        });
        
        DSU dsu(n);
        long long total_weight = 0;
        vector<pair<int, int>> mst_edges;
        for (auto& e : edges) {
            if (dsu.unite(e.u, e.v)) {
                total_weight += e.w;
                mst_edges.push_back({e.u, e.v});
            }
        }
        return {total_weight, mst_edges};
    }

    // ==========================================
    // 6. 最短路 (Dijkstra - 不支持负权)
    // ==========================================
    vector<long long> dijkstra(int start) {
        vector<long long> dist(n, INF);
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
        dist[start] = 0;
        pq.push({0, start});
        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (d > dist[u]) continue;
            for (auto& edge : adj[u]) {
                int v = edge.to;
                if (dist[u] + edge.weight < dist[v]) {
                    dist[v] = dist[u] + edge.weight;
                    pq.push({dist[v], v});
                }
            }
        }
        return dist;
    }

    // ==========================================
    // 7. 最短路 (Bellman-Ford - 支持负权并检测负环)
    // ==========================================
    pair<vector<long long>, bool> bellman_ford(int start) {
        vector<long long> dist(n, INF);
        dist[start] = 0;
        bool negative_cycle = false;
        for (int i = 0; i < n; ++i) {
            bool relaxed = false;
            for (int u = 0; u < n; ++u) {
                if (dist[u] == INF) continue;
                for (auto& edge : adj[u]) {
                    if (dist[u] + edge.weight < dist[edge.to]) {
                        dist[edge.to] = dist[u] + edge.weight;
                        relaxed = true;
                        if (i == n - 1) negative_cycle = true;
                    }
                }
            }
            if (!relaxed) break;
        }
        return {dist, negative_cycle};
    }

    // ==========================================
    // 8. 多源最短路 (Floyd-Warshall)
    // ==========================================
    vector<vector<long long>> floyd_warshall() {
        vector<vector<long long>> dist(n, vector<long long>(n, INF));
        for (int i = 0; i < n; ++i) dist[i][i] = 0;
        for (int u = 0; u < n; ++u)
            for (auto& edge : adj[u])
                dist[u][edge.to] = min(dist[u][edge.to], edge.weight);
        
        for (int k = 0; k < n; ++k)
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                    if (dist[i][k] < INF && dist[k][j] < INF)
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        return dist;
    }

    // ==========================================
    // 9. 最近公共祖先 LCA (基于倍增 Binary Lifting)
    // ==========================================
    void build_lca(int root = 0) {
        LOG = 1;
        while ((1 << LOG) <= n) LOG++;
        up.assign(n, vector<int>(LOG, -1));
        depth.assign(n, 0);
        auto dfs = [&](auto& self, int u, int p, int d) -> void {
            depth[u] = d;
            up[u][0] = p;
            for (int i = 1; i < LOG; ++i) {
                if (up[u][i - 1] != -1)
                    up[u][i] = up[up[u][i - 1]][i - 1];
                else
                    up[u][i] = -1;
            }
            for (auto& edge : adj[u]) {
                if (edge.to != p) self(self, edge.to, u, d + 1);
            }
        };
        dfs(dfs, root, -1, 0);
    }

    int get_lca(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        int diff = depth[u] - depth[v];
        for (int i = 0; i < LOG; ++i)
            if ((diff >> i) & 1) u = up[u][i];
        if (u == v) return u;
        for (int i = LOG - 1; i >= 0; --i) {
            if (up[u][i] != up[v][i]) {
                u = up[u][i];
                v = up[v][i];
            }
        }
        return up[u][0];
    }

    // ==========================================
    // 10. 网络流 (Dinic's Algorithm)
    // ==========================================
    long long dinic_max_flow(int s, int t) {
        vector<int> level(n), ptr(n);

        auto bfs_level = [&]() {
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            queue<int> q;
            q.push(s);
            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (auto& edge : adj[u]) {
                    if (edge.cap - edge.flow > 0 && level[edge.to] == -1) {
                        level[edge.to] = level[u] + 1;
                        q.push(edge.to);
                    }
                }
            }
            return level[t] != -1;
        };

        auto dfs_flow = [&](auto& self, int u, long long pushed) -> long long {
            if (u == t || pushed == 0) return pushed;
            for (int& cid = ptr[u]; cid < adj[u].size(); ++cid) {
                auto& edge = adj[u][cid];
                int v = edge.to;
                if (level[u] + 1 != level[v] || edge.cap - edge.flow == 0) continue;
                long long tr = self(self, v, min(pushed, edge.cap - edge.flow));
                if (tr == 0) continue;
                edge.flow += tr;
                adj[v][edge.rev].flow -= tr;
                return tr;
            }
            return 0;
        };

        long long flow = 0;
        while (bfs_level()) {
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs_flow(dfs_flow, s, INF)) {
                flow += pushed;
            }
        }
        return flow;
    }
};