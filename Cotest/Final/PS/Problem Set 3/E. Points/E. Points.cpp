
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct Query {
    string cmd;
    int x;
    int y;
};

struct Node {
    int value;
    set<int> s;
    int left;
    int right;
    pair<int, int> range;
};

int build(vector<Node>& tree, pair<int, int> range);
void update(int root, vector<Node>& tree, int index, int value);
void remove(int root, vector<Node>& tree, int index, int value);
pair<int, int> search(int root, vector<Node>& tree, int x, int y);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> x;
    x.reserve(n);

    vector<Query> queries(n, {"", -1, -1});
    for (int i = 0; i < n; i++) {
        cin >> queries[i].cmd >> queries[i].x >> queries[i].y;
        x.push_back(queries[i].x);
    }

    sort(x.begin(), x.end(), [] (auto& a, auto& b) {
        return a < b;
    });

    x.erase(unique(x.begin(), x.end()), x.end());

    unordered_map<int, int> x_to_range_index;
    for (int i = 0; i < x.size(); i++) {
        x_to_range_index[x[i]] = i + 1;
    }

    vector<Node> tree;
    tree.reserve(4 * n);
    int root = build(tree, {1, x.size()});

    for (int i = 0; i < n; i++) {
        if (queries[i].cmd == "add") {
            update(root, tree, x_to_range_index[queries[i].x], queries[i].y);
        } else if (queries[i].cmd == "remove") {
            remove(root, tree, x_to_range_index[queries[i].x], queries[i].y);
        } else {
            pair<int, int> result = search(root, tree, x_to_range_index[queries[i].x], queries[i].y);
            if (result.first == -1) {
                cout << -1 << '\n';
            } else {
                cout << x[result.first - 1] << ' ' << result.second << '\n';
            }
        }
    }
}


int build(vector<Node>& tree, pair<int, int> range) {
    int i = tree.size();
    tree.push_back({-1, {}, -1, -1, range});
    if (range.first == range.second) {
        return i;
    } else {
        int mid = range.first + (range.second - range.first) / 2;
        int left = build(tree, {range.first, mid});
        int right = build(tree, {mid + 1, range.second});
        tree[i].left = left;
        tree[i].right = right;
        tree[i].value = max(tree[left].value, tree[right].value);
        return i;
    }
}


void update(int root, vector<Node>& tree, int index, int value) {
    if (tree[root].range.first == tree[root].range.second) {
        tree[root].s.insert(value);
        tree[root].value = max(tree[root].value, value);
    } else {
        int left = tree[root].left;
        int right = tree[root].right;
        if (index <= tree[left].range.second) {
            update(left, tree, index, value);
        } else {
            update(right, tree, index, value);
        }
        tree[root].value = max(tree[left].value, tree[right].value);
    }
}

void remove(int root, vector<Node>& tree, int index, int value) {
    if (tree[root].range.first == tree[root].range.second) {
        tree[root].s.erase(tree[root].s.find(value));
        if (!tree[root].s.empty()) {
            tree[root].value = *tree[root].s.rbegin();
        } else {
            tree[root].value = -1;
        }
    } else {
        int left = tree[root].left;
        int right = tree[root].right;
        if (index <= tree[left].range.second) {
            remove(left, tree, index, value);
        } else {
            remove(right, tree, index, value);
        }
        tree[root].value = max(tree[left].value, tree[right].value);
    }
}


pair<int, int> search(int root, vector<Node>& tree, int x, int y) {
    if (tree[root].range.second <= x || tree[root].value <= y) {
        return {-1, -1};
    } else if (tree[root].range.first == tree[root].range.second) {
        if (tree[root].value <= y) {
            return {-1, -1};
        } else {
            return {
                tree[root].range.first,
                *tree[root].s.upper_bound(y),
            };
        }
    } else {
        int left = tree[root].left;
        int right = tree[root].right;

        pair<int, int> left_result = search(left, tree, x, y);

        if (left_result.first != -1) {
            return left_result;
        } else {
            return search(right, tree, x, y);
        }
    }
}