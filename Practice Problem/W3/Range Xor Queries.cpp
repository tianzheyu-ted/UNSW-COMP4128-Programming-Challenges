
#include <vector>
#include <iostream>

using namespace std;

struct Node {
    long long value;
    pair<int, int> range;
    int left;
    int right;
};

long long search(int root, vector<Node>& tree, pair<int, int> range);
int create(vector<Node>& tree, pair<int, int> range, vector<long long>& x);

int main() {
    int n, q;
    cin >> n >> q;

    vector<long long> pref(n + 1, 0);
    vector<long long> x(n + 1, -1);

    for (int i = 0; i < n; i++) {
        cin >> x[i];
        // pref[i] = pref[i - 1] ^ x[i];
    }

    vector<Node> tree;
    tree.reserve(4 * n);

    int root = create(tree, {0, n - 1}, x);

    

    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        cout << search(root, tree, {a - 1, b - 1}) << '\n';
        // cout << (pref[b] ^ pref[a - 1]) << '\n';
    }
}

long long search(int root, vector<Node>& tree, pair<int, int> range) {
    if (tree[root].range == range) {
        return tree[root].value;
    } else {
        int left = tree[root].left;
        int right = tree[root].right;
        if (range.second <= tree[left].range.second) {
            return search(left, tree, range);
        } else if (range.first >= tree[right].range.first) {
            return search(right, tree, range);
        } else {
            return (
                search(left, tree, {range.first, tree[left].range.second})
                ^ search(right, tree, {tree[right].range.first, range.second})
            );
        }
    }
}

int create(vector<Node>& tree, pair<int, int> range, vector<long long>& x) {
    int i = tree.size();
    tree.push_back({-1, range, -1, -1});

    if (range.first == range.second) {
        tree[i].value = x[range.first];
    } else {
        int mid = range.first + (range.second - range.first) / 2;
        tree[i].left = create(tree, {range.first, mid}, x);
        tree[i].right = create(tree, {mid + 1, range.second}, x);
        tree[i].value = tree[tree[i].left].value ^ tree[tree[i].right].value;
    }

    return i;
}