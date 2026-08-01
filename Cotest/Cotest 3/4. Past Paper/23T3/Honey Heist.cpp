
#include <queue>
#include <tuple>
#include <vector>
#include <iostream>

using namespace std;

int main() {
    int n, r;
    cin >> n >> r;

    pair<int, int> bear_pos;
    pair<int, int> honey_pos;
    cin >> bear_pos.first >> bear_pos.second;
    cin >> honey_pos.first >> honey_pos.second;

    vector<vector<char>> grid(n + 1, vector<char>(n + 1, ' '));

    for (int k = 1; k <= r; k++) {
        int i, j;
        cin >> i >> j;
        grid[i][j] = '.';
    }

    grid[honey_pos.first][honey_pos.second] = '*';

    auto bfs = [] (pair<int, int> src, vector<vector<char>>& grid) {
        const int di[4] = {0, 0, -1, 1};
        const int dj[4] = {-1, 1, 0, 0};
        
        int n = grid.size();

        queue<tuple<int, int, int>> q;
        vector<vector<bool>> visited(n, vector<bool>(n, false));

        q.push({src.first, src.second, 0});
        visited[src.first][src.second] = true;

        while (q.size() > 0) {
            auto curr = q.front();
            q.pop();
            for (int i = 0; i < 4; i++) {
                int next_i = get<0>(curr) + di[i];
                int next_j = get<1>(curr) + dj[i];
                if (1 <= next_i && next_i <= n && 1 <= next_j && next_j <= n) {
                    if (grid[next_i][next_j] != '.' && !visited[next_i][next_j]) {
                        visited[next_i][next_j] = true;
                        if (grid[next_i][next_j] == '*') {
                            return get<2>(curr) + 1;
                        } else {
                            q.push({next_i, next_j, get<2>(curr) + 1});
                        }
                    }
                }
            }
        }

        return 0;
    };

    cout << bfs(bear_pos, grid) << '\n';
}