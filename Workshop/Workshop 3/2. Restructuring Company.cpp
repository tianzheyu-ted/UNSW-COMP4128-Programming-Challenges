
#include <vector>
#include <iostream>


using namespace std;


void join(int x, int y, vector<int>& parents);
int find(int x, vector<int>& parents);

int main() {
    int n, q;
    cin >> n >> q;

    vector<int> parents(n + 1, 0);
    vector<int> next_unmerged(n + 2);
    for (int i = 1; i < n + 2; i++) {
        if (i < n + 1) parents[i] = i;
        next_unmerged[i] = i;
    }

    for (int i = 0; i < q; i++) {
        int type, x, y;
        cin >> type >> x >> y;

        if (type == 1) {
            join(x, y, parents);
        } else if (type == 2) {
            int curr = find(x, next_unmerged);
            while (curr < y) {
                join(curr, curr + 1, parents);
                next_unmerged[curr] = find(curr + 1, next_unmerged);
                curr = find(curr + 1, next_unmerged);
            }
        } else if (type == 3) {
            if (find(x, parents) == find(y, parents)) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }
}


void join(int x, int y, vector<int>& parents) {
    int a = find(x, parents);
    int b = find(y, parents);
    if (a != b) {
        parents[a] = b;
    }
}

int find(int x, vector<int>& parents) {
    if (parents[x] == x) {
        return x;
    } else {
        int result = find(parents[x], parents);
        parents[x] = result;
        return result;
    }
}