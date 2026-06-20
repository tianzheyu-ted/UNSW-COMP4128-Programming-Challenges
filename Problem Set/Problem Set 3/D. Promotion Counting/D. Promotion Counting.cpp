
#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct Cow {
    int index;
    int manager;
    long long rating;
    vector<int> children;
};

struct Node {
    int value;
    int left;
    int right;
    pair<int, int> range;
};

int build(vector<Node>& tree, pair<int, int> range);
void update(int root, vector<Node>& tree, int index, int value);
int search(int root, vector<Node>& tree, pair<int, int> range);
void dfsRec(int src, vector<Cow>& cows, vector<pair<int, int>>& ranges, int& timer);

int main() {
    ifstream cin ("promote.in");
    ofstream cout ("promote.out");

    int n;
    cin >> n;

    vector<Cow> cows(n, {-1, -1, {}});
    for (int i = 0; i < n; i++) {
        cin >> cows[i].rating;
        cows[i].index = i;
    }

    for (int i = 1; i < n; i++) {
        int manager;
        cin >> manager;
        cows[i].manager = manager - 1;
        cows[cows[i].manager].children.push_back(i);
    }

    int timer = 0;
    vector<pair<int, int>> ranges(n, {-1, -1});
    dfsRec(0, cows, ranges, timer);

    vector<Node> tree;
    tree.reserve(4 * n);
    int root = build(tree, {1, n});

    sort(cows.begin(), cows.end(), [] (auto& a, auto& b) {
        return a.rating > b.rating;
    });
    
    vector<int> result(n, 0);
    for (int i = 0; i < n; i++) {
        result[cows[i].index] = search(root, tree, ranges[cows[i].index]);
        update(root, tree, ranges[cows[i].index].first, 1);
    }

    for (int i = 0; i < n; i++) {
        cout << result[i] << '\n';
    }
}


int build(vector<Node>& tree, pair<int, int> range) {
    int i = tree.size();
    tree.push_back({0, -1, -1, {range.first, range.second}});
    if (range.first == range.second) {
        return i;
    } else {
        int mid = range.first + (range.second - range.first) / 2;
        tree[i].left = build(tree, {range.first, mid});
        tree[i].right = build(tree, {mid + 1, range.second});
        return i;
    }
}


void update(int root, vector<Node>& tree, int index, int value) {
    if (tree[root].range.first == tree[root].range.second) {
        tree[root].value = value;
    } else {
        int left = tree[root].left;
        int right = tree[root].right;
        if (tree[left].range.first <= index && index <= tree[left].range.second) {
            update(left, tree, index, value);
        } else {
            update(right, tree, index, value);
        }
        tree[root].value = tree[left].value + tree[right].value;
    }
}


int search(int root, vector<Node>& tree, pair<int, int> range) {
    if (tree[root].range == range) {
        return tree[root].value;
    } else {
        int left = tree[root].left;
        int right = tree[root].right;
        if (range.second <= tree[left].range.second) {
            return search(left, tree, range);
        } else if (tree[right].range.first <= range.first) {
            return search(right, tree, range);
        } else {
            return (
                search(left, tree, {range.first, tree[left].range.second}) 
                + search(right, tree, {tree[right].range.first, range.second})
            );
        }
    }
}


void dfsRec(int src, vector<Cow>& cows, vector<pair<int, int>>& ranges, int& timer) {
    timer++;
    ranges[src].first = timer;
    for (auto child : cows[src].children) {
        dfsRec(child, cows, ranges, timer);
    }
    ranges[src].second = timer;
}