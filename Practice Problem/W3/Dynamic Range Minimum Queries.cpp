
#include <vector>
#include <iostream>

using namespace std;

struct Node {
    long long value;
    pair<int, int> range;
    int left;
    int right;
};

void update(int root, vector<Node>& tree, int index, int value);
long long search(int root, vector<Node>& tree, pair<int, int> range);
int create(vector<Node>& tree, pair<int, int> range, vector<long long>& x);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;

    vector<long long> x(n, -1);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }

    vector<Node> tree;
    tree.reserve(4 * n);
    
    int root = create(tree, {0, n - 1}, x);

    for (int i = 0; i < q; i++) {
        int type;
        cin >> type;

        if (type == 1) {
            int k, u;
            cin >> k >> u;
            update(root, tree, k - 1, u);
        } else if (type == 2) {
            int a, b;
            cin >> a >> b;
            cout << search(root, tree, {a - 1, b - 1}) << '\n';
        }
    }
}


void update(int root, vector<Node>& tree, int index, int value) {
    if (tree[root].range.first == tree[root].range.second && tree[root].range.first == index) {
        tree[root].value = value;
    } else {
        int left = tree[root].left;
        int right = tree[root].right;
        if (index <= tree[left].range.second) {
            update(left, tree, index, value);
        } else {
            update(right, tree, index, value);
        }
        tree[root].value = min(tree[left].value, tree[right].value);
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
            return min(
                search(left, tree, {range.first, tree[left].range.second}),
                search(right, tree, {tree[right].range.first, range.second})
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
        tree[i].value = min(tree[tree[i].left].value, tree[tree[i].right].value);
    }

    return i;
}