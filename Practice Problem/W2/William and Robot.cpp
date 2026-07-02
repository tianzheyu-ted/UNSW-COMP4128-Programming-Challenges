
#include <set>
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

struct Node {
    int counter;
    long long value;
    pair<int, int> range;
    int left;
    int right;
};

void search(int root, vector<Node>& tree);
void update(int root, vector<Node>& tree);
int create(vector<Node>& tree, pair<int, int> range, vector<int>& a);

int main() {
    int n;
    cin >> n;

    priority_queue<long long, vector<long long>, greater<long long>> pq;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        pq.push(a);
        if (pq.size() > (i + 2) / 2) {
            pq.pop();
        }
    }

    long long result = 0;
    while (pq.size() > 0) {
        result += pq.top();
        pq.pop();
    }

    cout << result << '\n';
}

int main_plain_greedy() {
    int n;
    cin >> n;

    vector<int> a(n, -1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<Node> tree;
    tree.reserve(4 * n);

    int root = create(tree, {0, n - 1}, a);

    long long score = 0;
    while (tree[root].counter > 0) {
        score += tree[root].value;
        search(root, tree);
        update(root, tree);
    }

    cout << score << '\n';

    return 0;
}


void search(int root, vector<Node>& tree) {
    if (tree[root].left == -1) {
        tree[root].value = -1;
        tree[root].counter = 0;
        return;
    } else {
        int left = tree[root].left;
        int right = tree[root].right;
        if (tree[root].value == tree[left].value) {
            search(left, tree);
        } else {
            search(right, tree);
        }
        tree[root].counter = tree[left].counter + tree[right].counter;
        tree[root].value = max(tree[left].value, tree[right].value);
    }
}


void update(int root, vector<Node>& tree) {
    if (tree[root].left == -1) {
        tree[root].value = -1;
        tree[root].counter = 0;
        return;
    } else {
        int left = tree[root].left;
        int right = tree[root].right;
        if (tree[left].counter > 0) {
            update(left, tree);
        } else {
            update(right, tree);
        }
        tree[root].counter = tree[left].counter + tree[right].counter;
        tree[root].value = max(tree[left].value, tree[right].value);
    }
}


int create(vector<Node>& tree, pair<int, int> range, vector<int>& a) {
    int i = tree.size();
    tree.push_back({-1, -1, range, -1, -1});

    if (range.first == range.second) {
        tree[i].counter = 1;
        tree[i].value = a[range.first];
    } else {
        int mid = range.first + (range.second - range.first) / 2;
        int left = create(tree, {range.first, mid}, a);
        int right = create(tree, {mid + 1, range.second}, a);
        tree[i].left = left;
        tree[i].right = right;
        tree[i].counter = tree[left].counter + tree[right].counter;
        tree[i].value = max(tree[left].value, tree[right].value);
    }

    return i;
}