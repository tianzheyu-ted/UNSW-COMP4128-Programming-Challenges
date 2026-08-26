
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
     * Dijkstra's Algorithm for Single-Source Shortest Path (SSSP)
     * 
     * @param start 起点节点的编号 (Source node)
     * @param adj   原图的邻接表 (Adjacency list)。假设 Edge 包含 .to 和 .weight 属性。
     * @return pair<vector<long long>, vector<int>>:
     *         - first:  距离数组 (dist)，dist[i] 表示从 start 到节点 i 的最短距离。无法到达则为 INF。
     *         - second: 前驱节点数组 (parent)，用于回溯还原最短路径。如果 parent[i] == -1，说明无前驱。
     * 
     * ============================================================================
     * 【兼容性说明】本函数完美兼容 0-index 和 1-index 两种建图方式。
     * 
     * 黄金法则：直接使用 adj.size() 作为容量基准 n，返回的数组大小完美匹配。
     * 
     * 场景 A: 0-indexed Graph (节点编号 0 到 N-1)
     * ----------------------------------------------------------------------------
     * - 数组开法: adj 的大小开 N。
     * - 调用方式: 传入真实的起点，如 dijkstra(0, adj)。
     * - 返回结果: dist 和 parent 的有效下标完美对应 0 到 N-1。
     * 
     * 场景 B: 1-indexed Graph (节点编号 1 到 N)
     * ----------------------------------------------------------------------------
     * - 数组开法: adj 的大小开 N + 1 (0 号节点为空壳节点)。
     * - 调用方式: 传入真实的起点，如 dijkstra(1, adj)。
     * - 返回结果: dist 和 parent 的有效下标为 1 到 N。
     *            0 号节点由于没有任何边与其相连，dist[0] 会永远保持为 INF，
     *            它作为一个“透明人”绝对不会影响 1 到 N 之间最短路径的计算，
     *            最后直接无视 dist[0] 即可。
     * ============================================================================
     */
    auto dijkstra = [] (int start, const vector<vector<Edge>>& adj) -> pair<vector<long long>, vector<int>> {
        int n = adj.size();
        const long long INF = 1e18;
        
        vector<long long> dist(n, INF);
        vector<int> parent(n, -1);
        
        priority_queue<pair<long long, int>, 
                    vector<pair<long long, int>>, 
                    greater<pair<long long, int>>> pq;
                    
        dist[start] = 0;
        pq.push({0, start});
        
        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (d > dist[u]) continue;
            for (const auto& edge : adj[u]) {
                int v = edge.to;
                long long w = edge.weight;
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }

        return {dist, parent};
    };

    int start = 1;
    int target = n;

    auto [dist, parent] = dijkstra(start, adj);

    // 还原从 target 到 start 的路径
    vector<int> path;
    for (int curr = target; curr != -1; curr = parent[curr]) {
        path.push_back(curr);
    }

    // 因为是从后往前找的，反转一下就是正向路径
    reverse(path.begin(), path.end());

    // 检查是否真的联通 (如果 target 是 start，或者是有效路径，头部一定是 start)
    if (path.empty() || path[0] != start) {
        cout << "无路可达 (No path found)\n";
    } else {
        for (int node : path) cout << node << " ";
    }
}