
#include <set>
#include <vector>
#include <iostream>
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

struct Edge {
    int from;
    int to;
    long long weight;
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<Edge>> adj(n + 1, vector<Edge>());
    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u].push_back({u, v, w});
        adj[v].push_back({v, u, w});
    }

    /**
     * Kruskal's Algorithm for Minimum Spanning Tree (MST)
     * 稀疏图 边少点多
     * @param adj 原图的邻接表 (Adjacency list)
     * @return pair<long long, vector<tuple<int, int, long long>>>:
     *         - first:  MST 的总边权 (total_weight)
     *         - second: 构成 MST 的所有边的集合，每条边表示为 {u, v, weight}
     * 
     * ============================================================================
     * 【兼容性说明】本函数完美兼容 0-index 和 1-index 两种建图方式。
     * 
     * 黄金法则：将容器实际的大小 n = adj.size() 视为基准，遍历从 0 到 n-1。
     * 
     * 场景 A: 0-indexed Graph (节点编号 0 到 N-1)
     * ----------------------------------------------------------------------------
     * - 数组开法: adj 的大小开 N。
     * - 循环行为: 外层循环 u 从 0 遍历到 N-1，完美提取所有真实节点的边。
     * - 并查集: DSU(n) 内部通常开 n+1，足够覆盖 0 到 N-1 的范围。
     * 
     * 场景 B: 1-indexed Graph (节点编号 1 到 N)
     * ----------------------------------------------------------------------------
     * - 数组开法: adj 的大小开 N + 1 (0 号节点为空壳节点，没有任何出边)。
     * - 循环行为: 外层循环 u 从 0 遍历到 N。
     *            当 u = 0 时，因为 0 号节点是空壳，没有边，直接被安全跳过。
     *            当 u 在 1 到 N 时，完美提取真实连通的边。
     * ============================================================================
     */
    auto kruskal = [] (vector<vector<Edge>>& adj) -> pair<long long, vector<tuple<int, int, long long>>> {
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
        vector<tuple<int, int, long long>> mst_edges;
        for (auto& e : edges) {
            if (dsu.unite(e.u, e.v)) {
                total_weight += e.w;
                mst_edges.push_back({e.u, e.v, e.w});
            }
        }
        return {total_weight, mst_edges};
    };
}