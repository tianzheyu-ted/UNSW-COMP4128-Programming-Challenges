
#include <vector>
#include <iostream>

using namespace std;

struct Node {
    long long value;
    int level;
    int left;
    int right;
    pair<int, int> range;
};

int create(vector<Node>& tree, vector<long long>& d, pair<int, int> range) {
    int i = tree.size();
    tree.push_back({-1, 1, -1, -1, range});

    if (range.first == range.second) {
        tree[i].value = d[range.first - 1];
    } else {
        int mid = range.first + (range.second - range.first) / 2;
        int left = create(tree, d, {range.first, mid});
        int right = create(tree, d, {mid + 1, range.second});
        tree[i].left = left;
        tree[i].right = right;
        tree[i].level = tree[left].level + 1;

        if (tree[left].level % 2) {
            tree[i].value = tree[left].value | tree[right].value;
        } else {
            tree[i].value = tree[left].value ^ tree[right].value;
        }
    }

    return i;
}

void update(int root, vector<Node>& tree, long long index, long long value) {
    if (tree[root].range.first == tree[root].range.second) {
        tree[root].value = value;
    } else {
        int left = tree[root].left;
        int right = tree[root].right;
        if (index <= tree[left].range.second) {
            update(left, tree, index, value);
        } else {
            update(right, tree, index, value);
        }

        if (tree[left].level % 2) {
            tree[root].value = tree[left].value | tree[right].value;
        } else {
            tree[root].value = tree[left].value ^ tree[right].value;
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<long long> a((1 << n), -1);
    for (long long i = 0; i < (1 << n); i++) {
        cin >> a[i];
    }

    vector<Node> tree;
    tree.reserve(4 * (1 << n));

    int root = create(tree, a, {1, (1 << n)});

    for (int i = 0; i < m; i++) {
        long long p, b;
        cin >> p >> b;
        update(root, tree, p, b);
        cout << tree[root].value << '\n';
    }
}