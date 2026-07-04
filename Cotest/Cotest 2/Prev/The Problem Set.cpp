
#include <vector>
#include <iostream>

using namespace std;


struct Node {
    long long total_time;
    long long max_difficulty;
    long long min_difficulty;
    bool increasing;
    bool decreasing;
    int left;
    int right;
    pair<int, int> range;
};


struct Result {
    long long total_time;
    long long max_difficulty;
    long long min_difficulty;
    bool increasing;
    bool decreasing;
};


int create(vector<Node>& tree, vector<long long>& d, pair<int, int> range) {
    int i = tree.size();
    tree.push_back({-1, -1, -1, false, false, -1, -1, range});

    if (range.first == range.second) {
        tree[i].decreasing = true;
        tree[i].increasing = true;
        tree[i].total_time = d[range.first - 1];
        tree[i].max_difficulty = d[range.first - 1];
        tree[i].min_difficulty = d[range.first - 1];
    } else {
        int mid = range.first + (range.second - range.first) / 2;
        int left = create(tree, d, {range.first, mid});
        int right = create(tree, d, {mid + 1, range.second});

        tree[i].left = left;
        tree[i].right = right;
        tree[i].total_time = tree[left].total_time + tree[right].total_time;
        tree[i].max_difficulty = max(tree[left].max_difficulty, tree[right].max_difficulty);
        tree[i].min_difficulty = min(tree[left].min_difficulty, tree[right].min_difficulty);

        if (
            tree[left].decreasing 
            && tree[right].decreasing 
            && tree[left].min_difficulty >= tree[right].max_difficulty
        ) {
            tree[i].decreasing = true;
        }

        if (
            tree[left].increasing 
            && tree[right].increasing 
            && tree[right].min_difficulty >= tree[left].max_difficulty
        ) {
            tree[i].increasing = true;
        }
    }

    return i;
}


void update(int root, vector<Node>& tree, int index, long long value) {
    if (tree[root].range.first == tree[root].range.second) {
        tree[root].total_time = value;
        tree[root].max_difficulty = value;
        tree[root].min_difficulty = value;
    } else {
        int left = tree[root].left;
        int right = tree[root].right;
        if (index <= tree[left].range.second) {
            update(left, tree, index, value);
        } else {
            update(right, tree, index, value);
        }

        tree[root].total_time = tree[left].total_time + tree[right].total_time;
        tree[root].max_difficulty = max(tree[left].max_difficulty, tree[right].max_difficulty);
        tree[root].min_difficulty = min(tree[left].min_difficulty, tree[right].min_difficulty);

        tree[root].decreasing = (
            tree[left].decreasing 
            && tree[right].decreasing 
            && tree[left].min_difficulty >= tree[right].max_difficulty
        );

        tree[root].increasing = (
            tree[left].increasing 
            && tree[right].increasing 
            && tree[right].min_difficulty >= tree[left].max_difficulty
        );
    }
}


struct Result search(int root, vector<Node>& tree, pair<int, int> range) {
    if (range == tree[root].range) {
        return {
            tree[root].total_time,
            tree[root].max_difficulty,
            tree[root].min_difficulty,
            tree[root].increasing,
            tree[root].decreasing
        };
    } else {
        int left = tree[root].left;
        int right = tree[root].right;
        if (range.second <= tree[left].range.second) {
            return search(left, tree, range);
        } else if (range.first >= tree[right].range.first) {
            return search(right, tree, range);
        } else {
            Result left_result = search(left, tree, {range.first, tree[left].range.second});
            Result right_result = search(right, tree, {tree[right].range.first, range.second});
            return {
                left_result.total_time + right_result.total_time,
                max(left_result.max_difficulty, right_result.max_difficulty),
                min(left_result.min_difficulty, right_result.min_difficulty),
                (
                    left_result.increasing
                    && right_result.increasing
                    && left_result.max_difficulty <= right_result.min_difficulty
                ),
                (
                    left_result.decreasing
                    && right_result.decreasing
                    && left_result.min_difficulty >= right_result.max_difficulty
                )
            };
        }
    }
}


int main() {
    int n, m;
    cin >> n >> m;

    vector<long long> d(n, -1);
    for (int i = 0; i < n; i++) {
        cin >> d[i];
    }


    vector<Node> tree;
    tree.reserve(4 * n);

    int root = create(tree, d, {1, n});


    for (int i = 0; i < m; i++) {
        char type;
        int x, y;
        cin >> type >> x >> y;

        if (type == 'U') {
            update(root, tree, x, y);
        } else if (type == 'M') {
            cout << search(root, tree, {x, y}).max_difficulty << '\n';
        } else if (type == 'S') {
            cout << search(root, tree, {x, y}).total_time << '\n';
        } else if (type == 'I') {
            cout << (search(root, tree, {x, y}).increasing) << '\n';
        } else if (type == 'D') {
            cout << (search(root, tree, {x, y}).decreasing) << '\n';
        }
    }
}