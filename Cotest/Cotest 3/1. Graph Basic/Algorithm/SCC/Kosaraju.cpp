
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n, e;
    cin >> n >> e;

    vector<vector<int>> adj(n + 1, vector<int>());
    vector<vector<int>> rev_adj(n + 1, vector<int>());
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        rev_adj[v].push_back(u);
    }

    /**
     * Kosaraju's Algorithm for Strongly Connected Components (SCC)
     * 
     * @param adj      原图的邻接表 (Adjacency list)
     * @param rev_adj  反图的邻接表 (Reversed adjacency list)
     * @return pair<int, vector<int>>:
     *         - first:  图中共划分出的 SCC 的总数量 (scc_counter)
     *         - second: 一个数组 (scc_array)，scc_array[u] 表示节点 u 所属的 SCC 编号
     * 
     * ============================================================================
     * 【兼容性说明】本函数完美兼容 0-index 和 1-index 两种建图方式，SCC 编号始终从 1 开始。
     * 
     * 场景 A: 0-indexed Graph (节点编号 0 到 N-1)
     * ----------------------------------------------------------------------------
     * - 数组开法: adj 和 rev_adj 的大小开 N。
     * - 返回值 first: 正好等于原图真实的 SCC 数量 (K)。
     * - 返回值 second: 下标 0 到 N-1 均有效。scc_array[u] 的值域为 [1, K]。
     * 
     * 场景 B: 1-indexed Graph (节点编号 1 到 N)
     * ----------------------------------------------------------------------------
     * - 数组开法: adj 和 rev_adj 的大小开 N + 1 (0 号节点为空壳节点)。
     * - 返回值 first: 等于原图真实的 SCC 数量 + 1 (因为孤立的 0 号节点会被单独划分为一个 SCC)。
     * - 返回值 second: 下标 1 到 N 是真实数据。scc_array[u] 的值域为 [1, 真实SCC数+1]。
     *                 (注: 0 号节点会被分配一个废弃的 SCC 编号，后续逻辑中直接无视 scc_array[0] 即可)。
     * ============================================================================
     */
    auto kosaraju = [] (vector<vector<int>>& adj, vector<vector<int>>& rev_adj) -> pair<int, vector<int>> {
        // --- Kosaraju 1 Step: Obtain topological order ---
        int n = adj.size();
        vector<bool> visited(n, false);
        vector<int> order;
        auto dfs1 = [&](auto& self, int u) -> void {
            visited[u] = true;
            for (int v : adj[u]) {
                if (!visited[v]) {
                    self(self, v);
                }
            }
            order.push_back(u);
        };
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs1(dfs1, i);
            }
        }
        reverse(order.begin(), order.end());

        // --- Kosaraju 2 Step: Extract strongly connected components ---
        int scc_counter = 0;
        vector<int> scc(n, 0);
        vector<bool> visited2(n, false);
        auto dfs2 = [&](auto& self, int u) -> void {
            visited2[u] = true;
            scc[u] = scc_counter;
            for (int v : rev_adj[u]) {
                if (!visited2[v]) {
                    self(self, v);
                }
            }
        };
        for (auto u : order) {
            if (!visited2[u]) {
                scc_counter++;
                dfs2(dfs2, u);
            }
        }
        return {scc_counter, scc};
    };

}