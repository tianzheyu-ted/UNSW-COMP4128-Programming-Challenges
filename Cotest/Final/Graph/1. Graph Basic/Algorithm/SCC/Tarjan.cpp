

#include <stack>
#include <vector>
#include <iostream>

using namespace std;

int main() {
    int n, e;
    cin >> n >> e;

    vector<vector<int>> adj(n + 1, vector<int>());
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    /**
     * Tarjan's Algorithm for Strongly Connected Components (SCC)
     * 
     * @param adj 原图的邻接表 (Adjacency list)
     * @return pair<int, vector<int>>:
     *         - first:  图中共划分出的 SCC 的总数量 (scc_counter)
     *         - second: 一个数组 (scc_array)，scc_array[u] 表示节点 u 所属的 SCC 编号
     * 
     * ============================================================================
     * 【兼容性说明】本函数完美兼容 0-index 和 1-index 两种建图方式，SCC 编号始终从 1 开始。
     * 
     * 场景 A: 0-indexed Graph (节点编号 0 到 N-1)
     * ----------------------------------------------------------------------------
     * - 数组开法: adj 的大小开 N。
     * - 返回值 first: 正好等于原图真实的 SCC 数量 (K)。
     * - 返回值 second: 下标 0 到 N-1 均有效。scc_array[u] 的值域为 [1, K]。
     * 
     * 场景 B: 1-indexed Graph (节点编号 1 到 N)
     * ----------------------------------------------------------------------------
     * - 数组开法: adj 的大小开 N + 1 (0 号节点为空壳节点)。
     * - 返回值 first: 等于原图真实的 SCC 数量 + 1 (因为孤立的 0 号节点会被单独划分为一个 SCC)。
     * - 返回值 second: 下标 1 到 N 是真实数据。scc_array[u] 的值域为 [1, 真实SCC数+1]。
     *                 (注: 由于 0 号节点是孤立的，它往往会第一个触发出栈，通常被分配为 SCC 1。
     *                 后续逻辑中直接无视 scc_array[0] 即可)。
     * ============================================================================
     */
    auto tarjan_scc = [] (vector<vector<int>>& adj) -> pair<int, vector<int>> {
        int n = adj.size();

        int timer = 0;
        int scc_counter = 0;
        vector<int> dfn(n, 0);
        vector<int> low(n, 0);
        vector<int> scc(n, 0);

        stack<int> st;
        vector<bool> in_stack(n, false);

        auto tarjan = [&] (auto& self, int u) -> void {
            timer++;
            dfn[u] = timer;
            low[u] = timer;
            st.push(u);
            in_stack[u] = true;
            for (auto v : adj[u]) {
                if (!dfn[v]) {
                    self(self, v);
                    low[u] = min(low[u], low[v]);
                } else if (in_stack[v]) {
                    low[u] = min(low[u], dfn[v]);
                }
            }
            if (dfn[u] == low[u]) {
                scc_counter++;
                while (true) {
                    int node = st.top();
                    st.pop();
                    in_stack[node] = false;
                    scc[node] = scc_counter;
                    if (node == u) break;
                }
            }
        };

        for (int i = 0; i < n; i++) {
            if (!dfn[i]) {
                tarjan(tarjan, i);
            }
        }

        return {scc_counter, scc};
    };
}