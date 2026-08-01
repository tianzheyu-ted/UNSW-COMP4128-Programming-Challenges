
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
     *  复杂度与使用场景 (考场决策树)
        •	时间复杂度： O(V³)
        •	空间复杂度： O(V²)
        •	何时使用 Floyd-Warshall？
            1.	题目明确要求求出“所有点对”的最短距离。
            2.	数据范围非常小：节点的总数量 <= 400。
                在绝大多数 1 秒时限的 C++ 评测机中，3重循环跑 400^3 ~= 6.4 * 10^7 次计算是最安全的，
                如果 V = 1000， 10^9 次运算必定超时 Time Limit Exceeded）。
            3.	图非常稠密（边非常多）或者你需要一个写起来绝对不会出错的算法来验证其它算法的正确性。
     */

    /**
     * Floyd-Warshall Algorithm for All-Pairs Shortest Path (APSP)
     * 
     * @param adj 原图的邻接表 (Adjacency list)。假设 Edge 包含 .to 和 .weight 属性。
     * @return tuple<bool, vector<vector<long long>>, vector<vector<int>>>:
     *         - get<0>: 布尔值 has_negative_cycle，如果图中存在负权环，返回 true。
     *         - get<1>: 二维距离矩阵 (dist)，dist[i][j] 表示节点 i 到节点 j 的最短距离。
     *         - get<2>: 二维路由矩阵 (nxt)，nxt[i][j] 表示从 i 走到 j 的最短路径上的“下一步”节点编号。
     * 
     * ============================================================================
     * 【兼容性说明】本函数完美兼容 0-index 和 1-index 两种建图方式。
     * 
     * 黄金法则：直接使用 adj.size() 作为容量基准 n，建立 n x n 的二维矩阵。
     * 
     * 场景 A: 0-indexed (节点 0 到 N-1)
     * 场景 B: 1-indexed (节点 1 到 N)
     * 在 1-index 中，0 号节点是个没有边的孤立点。
     * 在初始化时，dist[0][j] 和 dist[i][0] 会保持为 INF（除了 dist[0][0] = 0）。
     * 核心的三层循环遍历到 0 号节点时，由于距离是 INF，会被我们的 continue 剪枝直接跳过，
     * 绝对不会对 1 到 N 节点之间的最短路产生任何干扰！
     * ============================================================================
     */
    auto floyd_warshall = [] (const vector<vector<Edge>>& adj) -> tuple<bool, vector<vector<long long>>, vector<vector<int>>> {
        int n = adj.size(); // n 是邻接表的真实容量
        const long long INF = 1e18; // 使用极大值防止溢出
        
        // 初始化二维距离矩阵和路径路由矩阵
        vector<vector<long long>> dist(n, vector<long long>(n, INF));
        vector<vector<int>> nxt(n, vector<int>(n, -1)); 
        
        // 1. 将邻接表转化为邻接矩阵
        for (int i = 0; i < n; ++i) {
            dist[i][i] = 0; // 自己到自己的距离为 0
            for (const auto& edge : adj[i]) {
                int u = i;
                int v = edge.to;
                long long w = edge.weight;
                
                // 🚨 防御重边 (Parallel Edges)：两点之间可能有多条边，只保留最短的那条
                if (w < dist[u][v]) {
                    dist[u][v] = w;
                    nxt[u][v] = v; // 从 u 到 v 的下一步当然是 v
                }
            }
        }
        
        // 2. 核心动态规划 (3层嵌套循环，注意 k 必须在最外层！)
        // dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                // 剪枝：如果 i 根本到不了 k，就没必要尝试经过 k 去松弛别的点了
                // 这不仅能加速，还能防止 INF + 负权边 导致 INF 被无效缩小的 Bug
                if (dist[i][k] == INF) continue; 
                
                for (int j = 0; j < n; ++j) {
                    if (dist[k][j] == INF) continue;
                    
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        // 核心路径状态转移：从 i 到 j 如果借道 k，
                        // 那么 i 迈出的第一步，跟 i 走向 k 迈出的第一步是一模一样的！
                        nxt[i][j] = nxt[i][k]; 
                    }
                }
            }
        }
        
        // 3. 负权环检测：如果某个点到自己的距离变成了负数，说明图中必定存在负权环
        bool has_negative_cycle = false;
        for (int i = 0; i < n; ++i) {
            if (dist[i][i] < 0) {
                has_negative_cycle = true;
                break;
            }
        }
        
        return {has_negative_cycle, dist, nxt};
    };


    auto [has_neg_cycle, dist, nxt] = floyd_warshall(adj);

    if (has_neg_cycle) {
        cout << "图中存在负权环！\n";
    } else {
        int start = 1, target = 5; // 假设我们要查询 1 到 5 的路径

        if (dist[start][target] == 1e18) {
            cout << "无法到达\n";
        } else {
            cout << "最短距离为: " << dist[start][target] << "\n路径: ";
            
            // 正向循环直接输出路径
            vector<int> path;
            int curr = start;
            while (curr != target) {
                path.push_back(curr);
                curr = nxt[curr][target]; // 查询路由表：去 target 的下一步该走哪
            }
            path.push_back(target); // 别忘了把终点塞进去
            
            for (int node : path) cout << node << " ";
            cout << '\n';
        }
    }
}