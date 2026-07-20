
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct Element {
    int value;
    pair<int, int> pos;
    bool operator==(const Element& other) const {
        return pos == other.pos;
    }
};

struct DSU {
    vector<int> parent;

    DSU(int n) {
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

    void reset(int i) {
        parent[i] = i;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<Element> a_1D(n*m, {-1, {-1, -1}});
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a_1D[i * m + j].value; 
            a_1D[i * m + j].pos = {i, j};
        }
    }

    sort(a_1D.begin(), a_1D.end(), [] (auto& a, auto& b) {
        if (a.value == b.value) {
            return a.pos < b.pos;
        }
        return a.value < b.value;
    });


    DSU dsu(n + m);
    vector<int> MaxRow(n, 0);
    vector<int> MaxCol(m, 0);
    vector<int> comp_max(n + m, 0);
    vector<vector<int>> ans(n, vector<int>(m, 0));

    for (int i = 0; i < n * m; ) {
        int j = i;
        while (j < n * m && a_1D[j].value == a_1D[i].value) {
            j++;
        }

        for (int k = i; k < j; k++) {
            int r = a_1D[k].pos.first;
            int c = a_1D[k].pos.second;
            dsu.unite(r, c + n);
        }
        
        for (int k = i; k < j; k++) {
            int r = a_1D[k].pos.first;
            int c = a_1D[k].pos.second;
            int root = dsu.find(r);
            comp_max[root] = max({comp_max[root], MaxRow[r], MaxCol[c]});
        }

        for (int k = i; k < j; k++) {
            int r = a_1D[k].pos.first;
            int c = a_1D[k].pos.second;
            int root = dsu.find(r);
            int new_val = comp_max[root] + 1; 
            
            ans[r][c] = new_val;
            MaxRow[r] = max(MaxRow[r], new_val);
            MaxCol[c] = max(MaxCol[c], new_val);
        }

        for (int k = i; k < j; k++) {
            int r = a_1D[k].pos.first;
            int c = a_1D[k].pos.second;

            int root = dsu.find(r);
            comp_max[root] = 0; 

            dsu.reset(r);
            dsu.reset(c + n);
        }

        i = j;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << ans[i][j] << (j == m - 1 ? "" : " ");
        }
        cout << "\n";
    }

    return 0;
}