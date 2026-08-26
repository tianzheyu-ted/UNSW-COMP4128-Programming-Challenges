
#include <set>
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    set<int> appeared;
    vector<vector<bool>> adj_matrix(26, vector<bool>(26, false));

    for (int i = 0; i < n; i++) {
        string password;
        cin >> password;

        int base = -1;        
        for (int j = 0; j < password.size(); j++) {
            char ch = password[j];
            appeared.insert(ch - 'a');

            if (base == -1) {
                base = ch - 'a';
            } else {
                adj_matrix[base][ch - 'a'] = true;
                adj_matrix[ch - 'a'][base] = true;
            }
        }
    }

    vector<bool> visited(26, false);

    auto dfs = [&] (auto& self, int src) -> void {
        visited[src] = true;
        for (int k = 0; k < 26; k++) {
            if (adj_matrix[src][k] && !visited[k]) {
                self(self, k);
            }
        }
    };

    int counter = 0;
    for (int j = 0; j < 26; j++) {
        if (!visited[j]) {
            dfs(dfs, j);
            counter++;
        }
    }

    cout << counter - (26 - appeared.size()) << '\n';
}