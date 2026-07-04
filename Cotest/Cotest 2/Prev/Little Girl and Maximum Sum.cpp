
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct Node {
    long long sum;
    int left;
    int right;
    pair<int, int> range;
};

int create(vector<Node>& tree, vector<long long>& d, pair<int, int> range) {
    int i = tree.size();
    tree.push_back({-1, -1, -1, range});

    if (range.first == range.second) {
        tree[i].sum = d[range.first - 1];
    } else {
        int mid = range.first + (range.second - range.first) / 2;
        int left = create(tree, d, {range.first, mid});
        int right = create(tree, d, {mid + 1, range.second});
        tree[i].left = left;
        tree[i].right = right;
        tree[i].sum = tree[left].sum + tree[right].sum;
    }

    return i;
}


long long search(int root, vector<Node>& tree, pair<int, int> range) {
    if (range == tree[root].range) {
        return tree[root].sum;
    } else {
        int left = tree[root].left;
        int right = tree[root].right;
        if (range.second <= tree[left].range.second) {
            return search(left, tree, range);
        } else if (range.first >= tree[right].range.first) {
            return search(right, tree, range);
        } else {
            long long left_result = search(left, tree, {range.first, tree[left].range.second});
            long long right_result = search(right, tree, {tree[right].range.first, range.second});
            return left_result + right_result;
        }
    }
}


int main() {
    int n, q;
    cin >> n >> q;

    vector<int> a(n, -1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    sort(a.begin(), a.end(), [] (auto& x, auto& y) {
        return x > y;
    });

    vector<pair<int, int>> queries(q, {-1, -1});
    for (int i = 0; i < q; i++) {
        cin >> queries[i].first >> queries[i].second;
    }

    vector<int> temp(n + 1, 0);
    for (auto range : queries) {
        temp[range.first - 1]++;
        temp[range.second]--;
    }

    int curr = 0;
    vector<pair<int, int>> freq(n, {-1, -1});
    for (int i = 0; i < n; i++) {
        curr += temp[i];
        freq[i].first = curr;
        freq[i].second = i;
    }

    sort(freq.begin(), freq.end(), [] (auto& a, auto& b) {
        if (a.first == b.first) {
            return a.second < b.second;
        }
        return a.first > b.first;
    });


    vector<long long> d(n, -1);
    for (int i = 0; i < n; i++) {
        d[freq[i].second] = a[i];
    }

    vector<Node> tree;
    tree.reserve(4 * n);

    int root = create(tree, d, {1, n});

    long long sum = 0;
    for (auto query : queries) {
        sum += search(root, tree, query);
    }

    cout << sum << '\n';
}