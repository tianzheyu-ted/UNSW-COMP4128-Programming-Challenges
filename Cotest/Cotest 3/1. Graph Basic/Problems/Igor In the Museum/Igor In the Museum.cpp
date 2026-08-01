
#include <vector>
#include <iostream>

using namespace std;

const int di[4] = {0, 0, 1, -1};
const int dj[4] = {1, -1, 0, 0};

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<string> grid(n, "");
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    int tag = 0;
    vector<int> picture_numbers(n*m, 0);
    vector<vector<int>> tags(n, vector<int>(m, -1));

    auto dfs = [&] (auto& self, pair<int, int> src, int tag) {
        if (tags[src.first][src.second] != -1) {
            return;
        } else {
            tags[src.first][src.second] = tag;
            for (int i = 0; i < 4; i++) {
                int next_i = src.first + di[i];
                int next_j = src.second + dj[i];
                if (0 <= next_i && next_i < n && 0 <= next_j && next_j < m) {
                    if (grid[next_i][next_j] == '*') {
                        picture_numbers[tag]++;
                    } else {
                        self(self, {next_i, next_j}, tag);
                    }
                }
            }
        }
    };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] != '*' && tags[i][j] == -1) {
                dfs(dfs, {i, j}, tag);
                tag++;
            }
        }
    }

    for (int i = 0; i < k; i++) {
        int x, y;
        cin >> x >> y;
        tag = tags[x - 1][y - 1];
        cout << picture_numbers[tag] << '\n';
    }
}