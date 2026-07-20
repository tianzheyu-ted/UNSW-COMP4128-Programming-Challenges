
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    string left_wall, right_wall;
    cin >> left_wall >> right_wall;

    vector<vector<int>> adj(2 * n + 1, vector<int>());

    for (int i = 0; i < n; i++) {
        if (left_wall[i] != 'X') {
            if (i - 1 >= 0 && left_wall[i - 1] != 'X') {
                adj[i].push_back(i - 1);
            }
            if (i + 1 >= n || left_wall[i + 1] != 'X') {
                adj[i].push_back(i + 1);
            }
            if (i + k >= n) {
                adj[i].push_back(2 * n);
            } else if (right_wall[i + k] != 'X') {
                adj[i].push_back(i + n + k);
            }
        }

        if (right_wall[i] != 'X') {
            if (i - 1 >= 0 && right_wall[i - 1] != 'X') {
                adj[i + n].push_back(i + n - 1);
            }
            if (i + 1 >= n || right_wall[i + 1] != 'X') {
                adj[i + n].push_back(i + n + 1);
            }
            if (i + k >= n) {
                adj[i + n].push_back(2 * n);
            } else if (left_wall[i + k] != 'X') {
                adj[i + n].push_back(i + k);
            }
        }
    }

    auto q = queue<pair<int, int>>();
    vector<bool> visited(2 * n + 1, false);
    
    q.push({0, 0});

    while (q.size() > 0) {
        auto curr = q.front();
        q.pop();

        if (visited[curr.first]) continue;

        visited[curr.first] = true;

        if (curr.first == 2 * n) {
            cout << "YES\n";
            return 0;
        }

        for (auto next : adj[curr.first]) {
            int next_height = next % n;
            if (next_height >= curr.second + 1 || next == 2 * n) {
                q.push({next, curr.second + 1});
            }
        }
    }
    
    cout << "NO\n";
}   

