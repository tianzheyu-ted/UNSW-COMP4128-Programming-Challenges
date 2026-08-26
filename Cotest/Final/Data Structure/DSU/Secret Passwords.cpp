
#include <set>
#include <stack>
#include <vector>
#include <iostream>

using namespace std;

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
};

int main() {
    int n;
    cin >> n;

    DSU dsu = DSU(26);
    set<int> appeared;

    for (int i = 0; i < n; i++) {
        string password;
        cin >> password;
        int base;
        for (int j = 0; j < password.size(); j++) {
            char ch = password[j];
            appeared.insert(ch);
            if (j == 0) {
                base = ch - 'a';
            } else {
                dsu.unite(base, ch - 'a');
            }
        }
    }

    set<int> counter;
    for (int i = 0; i < 26; i++) {
        counter.insert(dsu.find(i));
    }

    cout << counter.size() - (26 - appeared.size()) << '\n';
}