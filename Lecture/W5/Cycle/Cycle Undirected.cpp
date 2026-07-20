
#include <vector>
#include <iostream>

using namespace std;

struct DSU {
    vector<int> parent;

    DSU (int n) {
        parent.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i; 
        }
    }
    
    int find(int i) {
        if (parent[i] == i) {
            return i;
        }
        return parent[i] = find(parent[i]); 
    }
    
    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j; 
            return true; 
        }
        return false; 
    }
};

int main() {
    int n, e;
    cin >> n >> e;

    DSU dsu(n);
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        if (!dsu.unite(u, v)) {
            cout << "true\n";
            return 0;
        }
    }
    cout << "false\n";
}