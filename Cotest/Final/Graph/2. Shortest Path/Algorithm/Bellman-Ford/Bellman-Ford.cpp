
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
     * Dijkstra 还是 Bellman-Ford？（考场决策树）
        1.	图中全都是正权边（或权值为 0）？
            •	无脑 Dijkstra。时间复杂度 O(E log V)，跑得飞快。
        2.	图中有负权边，但保证没有负权环？
            •	必须用 Bellman-Ford（或者它的队列优化版 SPFA）。Dijkstra 遇到负权边直接歇菜。
        3.	题目问你“是否存在走不完的圈、能不能无限刷分、能不能通过汇率差无限套利”？
            •	必须用 Bellman-Ford。看它的 has_negative_cycle 是否返回 true 就能瞬间秒杀。
     */

    /**
     * Bellman-Ford Algorithm for Single-Source Shortest Path (SSSP) with Negative Edges
     * 
     * 时间复杂度：O(V * E)
     * 空间复杂度：O(V)
     * 
     * @param start 起点节点的编号 (Source node)
     * @param adj   原图的邻接表 (Adjacency list)。假设 Edge 包含 .to 和 .weight 属性。
     * @return tuple<bool, vector<long long>, vector<int>>:
     *         - get<0>: 布尔值 has_negative_cycle，如果从起点出发能走到负权环，返回 true。
     *         - get<1>: 距离数组 (dist)，dist[i] 表示从 start 到节点 i 的最短距离。
     *         - get<2>: 前驱节点数组 (parent)，用于回溯还原最短路径。
     * 
     * ============================================================================
     * 【兼容性说明】本函数完美兼容 0-index 和 1-index 两种建图方式。
     * 
     * 黄金法则：外层节点遍历直接基于 adj.size()，也就是 n。
     * 
     * 场景 A: 0-indexed (节点 0 到 N-1)
     * 场景 B: 1-indexed (节点 1 到 N, 0 号节点为空壳)
     * 无论是哪种，只要外层基于 n，0 号空壳节点在 1-index 图中没有任何邻居，
     * 它永远不会去松弛其他节点，也不会被其他节点松弛 (dist[0] 保持为 INF)，
     * 完全就是图中的“小透明”，不会对真实的节点 1 到 N 产生任何影响！
     * ============================================================================
     */
    auto bellman_ford = [] (int start, const vector<vector<Edge>>& adj) -> tuple<bool, vector<long long>, vector<int>> {
        int n = adj.size(); // 以邻接表的真实容量为准
        const long long INF = 1e18; // 使用极大值防止溢出
        
        vector<long long> dist(n, INF);
        vector<int> parent(n, -1);
        
        dist[start] = 0;
        
        // 第一阶段：进行 n - 1 轮全局松弛 (因为在 V 个点的图中，任何最短路径最多包含 V - 1 条边)
        for (int i = 0; i < n - 1; ++i) {
            bool relaxed = false; // 优化：如果某轮没有任何节点被松弛，说明已经求得最优解，可提前退出
            
            for (int u = 0; u < n; ++u) {
                // 🚨 核心防御：只有当节点 u 已经被可达的最短路径更新过，我们才用它去松弛别人。
                // 否则 INF 加上一个负权边，会变成一个比 INF 稍微小一点的无效值，导致幽灵节点互相松弛！
                if (dist[u] == INF) continue;
                
                for (const auto& edge : adj[u]) {
                    int v = edge.to;
                    long long w = edge.weight;
                    
                    if (dist[u] + w < dist[v]) {
                        dist[v] = dist[u] + w;
                        parent[v] = u;
                        relaxed = true;
                    }
                }
            }
            
            if (!relaxed) break; // 提前剪枝，极大提升随机图的运行效率
        }
        
        // 第二阶段：再进行 1 轮全局松弛，专门用来检测负权环
        // 如果经过 n - 1 轮后还能被松弛，说明陷入了越绕越短的“负权环”
        bool has_negative_cycle = false;
        for (int u = 0; u < n; ++u) {
            if (dist[u] == INF) continue;
            for (const auto& edge : adj[u]) {
                int v = edge.to;
                long long w = edge.weight;
                if (dist[u] + w < dist[v]) {
                    has_negative_cycle = true;
                    break; // 只要发现一个负权环，就可以直接跳出了
                }
            }
            if (has_negative_cycle) break;
        }
        
        return {has_negative_cycle, dist, parent};
    };

}