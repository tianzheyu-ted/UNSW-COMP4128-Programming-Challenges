
#include <set>
#include <vector>
#include <iostream>

using namespace std;

int timer = 0;
bool has_bridge = false;
vector<pair<int, int>> directed_edges;

struct Junction {
    set<int> neighbors;
};

void dfs(int curr, int parent, vector<Junction>& junctions, vector<int>& tin, vector<int>& low);

int main() {
    int n, m;
    cin >> n >> m;

    vector<Junction> junctions(n + 1, {{}});
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        junctions[a].neighbors.insert(b);
        junctions[b].neighbors.insert(a);
    }

    vector<int> tin(n + 1, 0);
    vector<int> low(n + 1, 0);

    dfs(1, 0, junctions, tin, low);

    if (has_bridge) {
        cout << 0 << '\n';
    } else {
        for (auto edge : directed_edges) {
            cout << edge.first << ' ' << edge.second << '\n';
        }
    }

    // for (int j = 0; j < n; j++) {
    //     vector<bool> visited(n, false);
    //     vector<int> highest(n, -1);
    //     for (int i = 0; i < n; i++) {
    //         highest[i] = i;
    //     }

    //     if (j == dfs(j, junctions, visited, highest)) {
    //         break;
    //     }
    // }
}


void dfs(int curr, int parent, vector<Junction>& junctions, vector<int>& tin, vector<int>& low) {
    timer++;
    tin[curr] = timer;
    low[curr] = timer;

    for (int next : junctions[curr].neighbors) {
        if (next == parent) continue;
        if (tin[next]) {
            low[curr] = min(low[curr], tin[next]);
            if (tin[curr] > tin[next]) {
                directed_edges.push_back({curr, next});
            }
        } else {
            directed_edges.push_back({curr, next});
            dfs(next, curr, junctions, tin, low);
            low[curr] = min(low[curr], low[next]);
            if (low[next] > tin[curr]) {
                has_bridge = true;
            }
        }
        
    }
}


int dfs_old(int src, vector<Junction>& junctions, vector<bool>& visited, vector<int>& highest) {
    if (visited[src]) {
        return highest[src];
    } else {
        visited[src] = true;
        int result = src;
        for (auto junction : junctions[src].neighbors) {
            int temp = dfs_old(junction, junctions, visited, highest);
            if (temp > src) {
                return 1e9;
            }
            result = min(temp, result);
        }
        return result;
    }
}