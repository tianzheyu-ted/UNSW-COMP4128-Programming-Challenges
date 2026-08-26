
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    string left_wall, right_wall;
    cin >> left_wall >> right_wall;

    static int RIGHT_BASE = 0;
    static int LEFT_BASE = n;
    static int END = 2 * n + 1;
    vector<vector<int>> adj(2 * n + 2, vector<int>());

    // right
    for (int i = 1; i <= n; i++) {
        if (right_wall[i - 1] != 'X') {
            if (i + 1 > n) adj[i].push_back(END);
            if (i + 1 <= n && right_wall[i] != 'X') adj[i].push_back(i + 1);
            if (i - 1 > 0 && right_wall[i - 2] != 'X') adj[i].push_back(i - 1);
            if (i + k > n) adj[i].push_back(END);
            if (i + k <= n && left_wall[i - 1 + k] != 'X') adj[i].push_back(LEFT_BASE + i + k);
        }
    }

    // left
    for (int i = 1; i <= n; i++) {
        if (left_wall[i - 1] != 'X') {
            if (i + 1 > n) adj[LEFT_BASE + i].push_back(END);
            if (i + 1 <= n && left_wall[i] != 'X') adj[LEFT_BASE + i].push_back(LEFT_BASE + i + 1);
            if (i - 1 > 0 && left_wall[i - 2] != 'X') adj[LEFT_BASE + i].push_back(LEFT_BASE + i - 1);
            if (i + k > n) adj[LEFT_BASE + i].push_back(END);
            if (i + k <= n && right_wall[i - 1 + k] != 'X') adj[LEFT_BASE + i].push_back(i + k);
        }
    }

    vector<bool> visited(2 * n + 2, false);
    auto bfs = [&] (int src) {
        auto get_height = [&] (int curr) -> int {
            if (curr == END) return 1e9;

            if (curr % n != 0) {
                return curr % n;
            } else {
                if (curr / n > 0) {
                    return n;
                } else {
                    return 0;
                }
            }
        };

        queue<pair<int, int>> q;
        q.push({LEFT_BASE + 1, 0});
        visited[src] = true;

        while (!q.empty()) {
            auto curr = q.front(); q.pop();
            for (auto& next : adj[curr.first]) {
                if (!visited[next] && get_height(next) > curr.second + 1) {
                    q.push({next, curr.second + 1});
                    visited[next] = true;
                }
            }
        }
    };

    bfs(LEFT_BASE + 1);

    if (visited[END]) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}