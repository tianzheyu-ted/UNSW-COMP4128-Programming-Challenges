
#include <vector>
#include <iostream>

using namespace std;

void dfs(pair<int, int> src, vector<vector<char>>& museum, vector<vector<int>>& visited, int marker, vector<int>& picture_nums);

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<char>> museum(n, vector<char>(m, ' '));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> museum[i][j];
        }
    }

    vector<int> picture_nums(n * m, 0);
    vector<vector<int>> visited(n, vector<int>(m, 0));

    int marker = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!visited[i][j] && museum[i][j] != '*') {
                dfs({i, j}, museum, visited, marker, picture_nums);
                marker++;
            }
        }
    }

    for (int i = 0; i < k; i++) {
        int x, y;
        cin >> x >> y;
        cout << picture_nums[visited[x - 1][y - 1] - 1] << '\n';
    }
}


void dfs(pair<int, int> src, vector<vector<char>>& museum, vector<vector<int>>& visited, int marker, vector<int>& picture_nums) {
    if (visited[src.first][src.second]) {
        return;
    }

    if (museum[src.first][src.second] == '*') {
        picture_nums[marker - 1] += 1;
        return;
    }

    visited[src.first][src.second] = marker;

    if (src.first - 1 >= 0) {
        dfs({src.first - 1, src.second}, museum, visited, marker, picture_nums);
    }

    if (src.first + 1 <= museum.size()) {
        dfs({src.first + 1, src.second}, museum, visited, marker, picture_nums);
    }
    
    if (src.second - 1 >= 0) {
        dfs({src.first, src.second - 1}, museum, visited, marker, picture_nums);
    }

    if (src.second + 1 <= museum[0].size()) {
        dfs({src.first, src.second + 1}, museum, visited, marker, picture_nums);
    }
}