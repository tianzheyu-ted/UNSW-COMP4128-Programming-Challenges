
#include <set>
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

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
     * Prim's Algorithm for Minimum Spanning Tree / Forest (MST / MSF)
     * 稠密图 边多点少
     * @param adj 原图的邻接表 (Adjacency list)。假设 Edge 包含 .to 和 .weight 属性。
     * @return pair<long long, vector<tuple<int, int, long long>>>:
     *         - first:  MST 的总边权 (total_weight)
     *         - second: 构成 MST 的所有边的集合，每条边表示为 {u, v, weight}
     * 
     * ============================================================================
     * 【兼容性说明】本函数完美兼容 0-index 和 1-index 两种建图方式。
     * 
     * 黄金法则：以 adj.size() 作为容量基准 n，外层循环从 0 遍历到 n-1。
     * 
     * 为什么能兼容 1-index 的空壳 0 号点？
     * 当 i = 0 时，如果图是 1-indexed，0 号点没有任何邻居。
     * 代码会将其标记为已访问 (in_mst[0] = true)，然后优先队列保持为空，直接跳过。
     * 接下来 i = 1 时，真正的 Prim 扩张就会从 1 号节点正常启动，完全不受 0 号点的干扰。
     * 
     * 为什么能兼容不连通图？
     * 外层的 for 循环使得算法能求出“最小生成森林”。哪怕图由多个孤立的连通块组成，
     * 每次遇到未访问的块就会启动一次新的 Prim 扩张，非常安全。
     * ============================================================================
     */
    auto prim = [] (const vector<vector<Edge>>& adj) -> pair<long long, vector<tuple<int, int, long long>>> {
        int n = adj.size();
        long long total_weight = 0;
        vector<tuple<int, int, long long>> mst_edges;
        vector<bool> in_mst(n, false);
        
        priority_queue<tuple<long long, int, int>, 
                    vector<tuple<long long, int, int>>, 
                    greater<tuple<long long, int, int>>> pq;

        for (int start_node = 0; start_node < n; ++start_node) {
            if (in_mst[start_node]) continue;
            
            in_mst[start_node] = true;
            for (const auto& edge : adj[start_node]) {
                pq.push({edge.weight, edge.to, start_node});
            }
            
            while (!pq.empty()) {
                auto [w, v, u] = pq.top();
                pq.pop();
                if (in_mst[v]) continue;
                in_mst[v] = true;
                total_weight += w;
                mst_edges.push_back({u, v, w});
                for (const auto& edge : adj[v]) {
                    if (!in_mst[edge.to]) {
                        pq.push({edge.weight, edge.to, v});
                    }
                }
            }
        }
        
        return {total_weight, mst_edges};
    };
}