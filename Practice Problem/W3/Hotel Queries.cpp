
#include <vector>
#include <iostream>

using namespace std;

struct Node {
    long long max_value;
    long long min_value;
    pair<int, int> range;
    int left;
    int right;
};

void update(int root, vector<Node>& tree, int index, int value);
pair<int, long long> search(int root, vector<Node>& tree, pair<int, int> range, long long target);
int create(vector<Node>& tree, pair<int, int> range, vector<long long>& x);

int main() {
    int n, m;
    cin >> n >> m;

    vector<long long> hotels(n, -1);
    for (int i = 0; i < n; i++) {
        cin >> hotels[i];
    }

    vector<Node> tree;
    tree.reserve(4 * n);

    int root = create(tree, {0, n - 1}, hotels);

    for (int i = 0; i < m; i++) {
        long long r;
        cin >> r;

        pair<int, long long> item = search(root, tree, {0, n - 1}, r);
        if (item.first != 0) {
            update(root, tree, item.first - 1, item.second - r);
        }
        
        cout << item.first << ' ';
    }
    cout << '\n';
}


void update(int root, vector<Node>& tree, int index, int value) {
    if (tree[root].range.first == tree[root].range.second && tree[root].range.first == index) {
        tree[root].min_value = value;
        tree[root].max_value = value;
    } else {
        int left = tree[root].left;
        int right = tree[root].right;
        if (index <= tree[left].range.second) {
            update(left, tree, index, value);
        } else {
            update(right, tree, index, value);
        }
        tree[root].min_value = min(tree[left].min_value, tree[right].min_value);
        tree[root].max_value = max(tree[left].max_value, tree[right].max_value);
    }
}


pair<int, long long> search(int root, vector<Node>& tree, pair<int, int> range, long long target) {
    if (target > tree[root].max_value) {
        return {0, -1};
    } else {
        if (range.first == range.second) {
            return {range.first + 1, tree[root].max_value};
        } else {
            int left = tree[root].left;
            int right = tree[root].right;
            if (target <= tree[left].max_value) {
                return search(left, tree, tree[left].range, target);
            } else {
                return search(right, tree, tree[right].range, target);
            }
        }
    }
}


int create(vector<Node>& tree, pair<int, int> range, vector<long long>& x) {
    int i = tree.size();
    tree.push_back({-1, -1, range, -1, -1});

    if (range.first == range.second) {
        tree[i].max_value = x[range.first];
        tree[i].min_value = x[range.second];
    } else {
        int mid = range.first + (range.second - range.first) / 2;
        tree[i].left = create(tree, {range.first, mid}, x);
        tree[i].right = create(tree, {mid + 1, range.second}, x);
        tree[i].max_value = max(tree[tree[i].left].max_value, tree[tree[i].right].max_value);
        tree[i].min_value = min(tree[tree[i].left].min_value, tree[tree[i].left].min_value);
    }

    return i;
}