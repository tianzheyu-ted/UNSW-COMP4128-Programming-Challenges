#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

// 记录 BFS 队列中的状态
struct State {
    int x, y, steps;
};

int main() {
    // 优化标准输入输出流速度，防止在大数据量下超时
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, r;
    if (!(cin >> n >> r)) return 0;

    int sx, sy, hx, hy;
    cin >> sx >> sy >> hx >> hy;

    // 分别记录每一行和每一列的石头坐标
    // 大小开 n + 1 以便使用 1-based 索引
    vector<vector<int>> row_rocks(n + 1);
    vector<vector<int>> col_rocks(n + 1);

    for (int i = 0; i < r; ++i) {
        int rx, ry;
        cin >> rx >> ry;
        row_rocks[rx].push_back(ry);
        col_rocks[ry].push_back(rx);
    }

    // 对所有的行和列内的石头进行排序，方便后续二分查找
    for (int i = 1; i <= n; ++i) {
        if (!row_rocks[i].empty()) sort(row_rocks[i].begin(), row_rocks[i].end());
        if (!col_rocks[i].empty()) sort(col_rocks[i].begin(), col_rocks[i].end());
    }

    queue<State> q;
    set<pair<int, int>> visited; // 记录已经到达过的静止状态点

    q.push({sx, sy, 0});
    visited.insert({sx, sy});

    while (!q.empty()) {
        State curr = q.front();
        q.pop();
        
        int x = curr.x;
        int y = curr.y;
        int steps = curr.steps;

        // ----------------- 1. 向右滑 -----------------
        int ny = n; // 默认滑到底
        // upper_bound 找到当前行中，列号严格大于当前 y 的第一个石头
        auto it_r = upper_bound(row_rocks[x].begin(), row_rocks[x].end(), y);
        if (it_r != row_rocks[x].end()) {
            ny = *it_r - 1; // 停在石头的前一格
        }
        // 检查滑行轨迹是否经过蜂蜜罐
        if (hx == x && hy >= y && hy <= ny) {
            cout << steps + 1 << "\n";
            return 0;
        }
        // 如果位置发生变化且未被访问过，则加入队列
        if (ny != y && visited.find({x, ny}) == visited.end()) {
            visited.insert({x, ny});
            q.push({x, ny, steps + 1});
        }

        // ----------------- 2. 向左滑 -----------------
        ny = 1; // 默认滑到最左
        // lower_bound 找到当前行中，列号大于等于当前 y 的第一个石头
        auto it_l = lower_bound(row_rocks[x].begin(), row_rocks[x].end(), y);
        // 如果它不是第一个元素，说明它左边一定有石头
        if (it_l != row_rocks[x].begin()) {
            it_l--; // 退一位拿到它左边的那个石头
            ny = *it_l + 1; // 停在石头右侧一格
        }
        if (hx == x && hy >= ny && hy <= y) {
            cout << steps + 1 << "\n";
            return 0;
        }
        if (ny != y && visited.find({x, ny}) == visited.end()) {
            visited.insert({x, ny});
            q.push({x, ny, steps + 1});
        }

        // ----------------- 3. 向下滑 -----------------
        int nx = n; // 默认滑到最底
        // upper_bound 找到当前列中，行号严格大于当前 x 的第一个石头
        auto it_d = upper_bound(col_rocks[y].begin(), col_rocks[y].end(), x);
        if (it_d != col_rocks[y].end()) {
            nx = *it_d - 1;
        }
        if (hy == y && hx >= x && hx <= nx) {
            cout << steps + 1 << "\n";
            return 0;
        }
        if (nx != x && visited.find({nx, y}) == visited.end()) {
            visited.insert({nx, y});
            q.push({nx, y, steps + 1});
        }

        // ----------------- 4. 向上滑 -----------------
        nx = 1; // 默认滑到最顶
        auto it_u = lower_bound(col_rocks[y].begin(), col_rocks[y].end(), x);
        if (it_u != col_rocks[y].begin()) {
            it_u--;
            nx = *it_u + 1;
        }
        if (hy == y && hx >= nx && hx <= x) {
            cout << steps + 1 << "\n";
            return 0;
        }
        if (nx != x && visited.find({nx, y}) == visited.end()) {
            visited.insert({nx, y});
            q.push({nx, y, steps + 1});
        }
    }

    // 队列清空依然没有碰到蜂蜜罐，说明无解
    cout << 0 << "\n";
    return 0;
}