
#include <set>
#include <vector>
#include <iostream>

using namespace std;

void dfsRec(int src, vector<vector<bool>>& adj_matrix, vector<bool>& visited);

int main() {
    int n;
    cin >> n;

    set<int> appear;
    vector<vector<bool>> adj_matrix(26, vector<bool>(26, false));
    for (int i = 0; i < n; i++) {
        string password;
        cin >> password;

        for (int j = 0; j < password.size(); j++) {
            appear.insert(password[j] - 'a');
            for (int k = 0; k < j; k++) {
                int u = password[j] - 'a';
                int v = password[k] - 'a';
                adj_matrix[u][v] = true;
                adj_matrix[v][u] = true;
            }
        }
    }

    int result = 0;
    vector<bool> visited(26, false);
    for (int i = 0; i < 26; i++) {
        if (appear.count(i) && !visited[i]) {
            result++;
            dfsRec(i, adj_matrix, visited);
        }
    }

    cout << result << '\n';
}


void dfsRec(int src, vector<vector<bool>>& adj_matrix, vector<bool>& visited) {
    if (visited[src]) {
        return;
    } else {
        visited[src] = true;
        for (int i = 0; i < adj_matrix[0].size(); i++) {
            if (adj_matrix[src][i]) {
                dfsRec(i, adj_matrix, visited);
            }
        }
    }
} 