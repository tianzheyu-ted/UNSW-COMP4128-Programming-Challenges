
#include <vector>
#include <cmath>
#include <iostream>


using namespace std;

struct Node {
    long long height;
    long long value;
    long long left;
    long long right;
    pair<long long, long long> range;
};

int build(vector<Node>& tree, vector<long long>& a, pair<long long, long long> range);
void update(long long root, vector<Node>& tree, long long p, long long b);

int main() {
    int n, m;
    cin >> n >> m;

    vector<long long> a(round(pow(2, n)), -1);
    for (long long i = 0; i < round(pow(2, n)); i++) {
        cin >> a[i];
    }

    vector<Node> tree;
    tree.reserve(4 * round(pow(2, n)));
    int root = build(tree, a, {0, round(pow(2, n)) - 1});

    // cout << root << '\n';

    for (long long i = 0; i < m; i++) {
        long long p, b;
        cin >> p >> b;
        update(root, tree, p - 1, b);
        cout << tree[root].value << '\n';
    }
}


int build(vector<Node>& tree, vector<long long>& a, pair<long long, long long> range) {
    long long i = tree.size();
    tree.push_back({-1, -1, -1, -1, {-1, -1}});

    if (range.first == range.second) {
        tree[i].height = 0;
        tree[i].range = range;
        tree[i].value = a[range.first];
        return i;
    } else {
        long long mid = range.first + (range.second - range.first) / 2;
        long long left = build(tree, a, {range.first, mid});
        long long right = build(tree, a, {mid + 1, range.second});

        tree[i].left = left;
        tree[i].right = right;
        tree[i].range = range;
        tree[i].height = tree[left].height + 1;

        if (tree[i].height % 2 == 1) {
            tree[i].value = tree[left].value | tree[right].value;
        } else {
            tree[i].value = tree[left].value ^ tree[right].value;
        }

        return i;
    }
}


void update(long long root, vector<Node>& tree, long long p, long long b) {
    if (tree[root].range.first == tree[root].range.second) {
        tree[root].value = b;
    } else {
        long long left = tree[root].left;
        long long right = tree[root].right;

        if (tree[left].range.first <= p && p <= tree[left].range.second) {
            update(left, tree, p, b);
        } else if (tree[right].range.first <= p && p <= tree[right].range.second) {
            update(right, tree, p, b);
        }


        if (tree[root].height % 2 == 1) {
            tree[root].value = tree[left].value | tree[right].value;
        } else {
            tree[root].value = tree[left].value ^ tree[right].value;
        }
    }
}
