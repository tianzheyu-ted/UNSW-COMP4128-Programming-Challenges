
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct Vertex {
    int vertex;
    set<int> neighbors;
    pair<int, int> range;
};

struct Node {
    bool water;
    bool children_water_tag;
    int left;
    int right;
    pair<int, int> range;
};


int build(vector<Node>& tree, pair<int, int> range);
void updateUp(int root, vector<Node>& tree, int index);
void updateDown(int root, vector<Node>& tree, pair<int, int> range);
bool search(int root, vector<Node>& tree, pair<int, int> range);
void dfsRec(int src, int parent, vector<Vertex>& graph, int& timer, vector<int>& parent_node);
void pushUp(int root, vector<Node>& tree);
void pushDown(int root, vector<Node>& tree);


int main() {
    int n;
    cin >> n;
    
    vector<Vertex> graph(n + 1, {-1, {}});
    graph[1].vertex = 1;
    
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].neighbors.insert(b);
        graph[b].neighbors.insert(a);
    }

    int timer = 0;
    vector<int> parent_node(n + 1, 0);
    dfsRec(1, 0, graph, timer, parent_node);

    vector<Node> tree;
    tree.reserve(4 * n);
    int root = build(tree, {1, timer});

    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int c, v;
        cin >> c >> v;
        if (c == 1) {
            if (!search(root, tree, graph[v].range) && parent_node[v] != 0) {
                updateUp(root, tree, graph[parent_node[v]].range.first);
            }
            updateDown(root, tree, graph[v].range);
        } else if (c == 2) {
            updateUp(root, tree, graph[v].range.first);
        } else if (c == 3) {
            cout << search(root, tree, graph[v].range) << '\n';
        }
    }
}


int build(vector<Node>& tree, pair<int, int> range) {
    int i = tree.size();
    tree.push_back({false, false, -1, -1, range});
    if (range.first == range.second) {
        return i;
    } else {
        int mid = range.first + (range.second - range.first) / 2;
        tree[i].left = build(tree, {range.first, mid});
        tree[i].right = build(tree, {mid + 1, range.second});
        return i;
    }
}


void updateUp(int root, vector<Node>& tree, int index) {
    if (tree[root].range.first == tree[root].range.second) {
        tree[root].water = false;
        tree[root].children_water_tag = false;
        return;
    } else {
        pushDown(root, tree);

        int left = tree[root].left;
        int right = tree[root].right;
        if (index <= tree[left].range.second) {
            updateUp(left, tree, index);
        } else if (index >= tree[right].range.first) {
            updateUp(right, tree, index);
        }
        
        tree[root].water = false;
        tree[root].children_water_tag = false;
    }
}

void pushDown(int root, vector<Node>& tree) {
    if (tree[root].children_water_tag) {
        int left = tree[root].left;
        int right = tree[root].right;
        if (left != -1) {
            tree[left].water = true;
            tree[left].children_water_tag = true;
        }
        if (right != -1) {
            tree[right].water = true;
            tree[right].children_water_tag = true;
        }
        tree[root].children_water_tag = false; 
    }
}

void pushUp(int root, vector<Node>& tree) {
    int left = tree[root].left;
    int right = tree[root].right;
    if (left != -1 && right != -1) {
        tree[root].water = (tree[left].water && tree[right].water);
    }
}

void updateDown(int root, vector<Node>& tree, pair<int, int> range) {
    int left = tree[root].left;
    int right = tree[root].right;
    if (tree[root].range == range) {
        tree[root].water = true;
        tree[root].children_water_tag = true;
    } else {
        pushDown(root, tree);

        if (range.second <= tree[left].range.second) {
            updateDown(left, tree, range);
        } else if (range.first >= tree[right].range.first) {
            updateDown(right, tree, range);
        } else {
            updateDown(left, tree, {range.first, tree[left].range.second});
            updateDown(right, tree, {tree[right].range.first, range.second});
        }

        pushUp(root, tree);
    }
}

bool search(int root, vector<Node>& tree, pair<int, int> range) {
    if (tree[root].range == range) {
        return tree[root].water;
    } else {
        if (tree[root].children_water_tag) {
            return true;
        }

        int left = tree[root].left;
        int right = tree[root].right;
        if (range.second <= tree[left].range.second) {
            return search(left, tree, range);
        } else if (range.first >= tree[right].range.first) {
            return search(right, tree, range);;
        } else {
            return (
                search(left, tree, {range.first, tree[left].range.second})
                && search(right, tree, {tree[right].range.first, range.second})
            );
        }
    }
}


void dfsRec(int src, int parent, vector<Vertex>& graph, int& timer, vector<int>& parent_node) {
    timer++;
    graph[src].range.first = timer;
    parent_node[src] = parent;
    for (auto next : graph[src].neighbors) {
        if (next != parent) {
            dfsRec(next, src, graph, timer, parent_node);
        }
    }
    graph[src].range.second = timer;
}