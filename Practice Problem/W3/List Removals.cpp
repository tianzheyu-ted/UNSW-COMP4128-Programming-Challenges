
#include <vector>
#include <iostream>

using namespace std;

struct Node {
    long long value;
    long long counter;
    pair<int, int> range;
    int left;
    int right;
};

int remove(int root, vector<Node>& tree, int index);
int create(vector<Node>& tree, pair<int, int> range, vector<long long>& x);

int main() {
    int n;
    cin >> n;

    vector<long long> x(n, -1);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }

    vector<Node> tree;
    tree.reserve(4 * n);

    int root = create(tree, {0, n - 1}, x);

    for (int i = 0; i < n; i++) {
        int p;
        cin >> p;
        cout << remove(root, tree, p) << ' ';
    }

    cout << '\n';
}


int remove(int root, vector<Node>& tree, int index) {
    if (tree[root].left == -1) {
        tree[root].counter = 0;
        return tree[root].value;
    } else {
        int left = tree[root].left;
        int right = tree[root].right;

        int result;
        if (index <= tree[left].counter) {
            result = remove(left, tree, index);
        } else {
            result = remove(right, tree, index - tree[left].counter);
        }

        tree[root].counter = tree[left].counter + tree[right].counter;
        return result;
    }
}


int create(vector<Node>& tree, pair<int, int> range, vector<long long>& x) {
    int i = tree.size();
    tree.push_back({-1, 0, range, -1, -1});

    if (range.first == range.second) {
        tree[i].value = x[range.first];
        tree[i].counter = 1;
    } else {
        int mid = range.first + (range.second - range.first) / 2;
        tree[i].left = create(tree, {range.first, mid}, x);
        tree[i].right = create(tree, {mid + 1, range.second}, x);
        tree[i].counter = tree[tree[i].left].counter + tree[tree[i].right].counter;
    }

    return i;
}