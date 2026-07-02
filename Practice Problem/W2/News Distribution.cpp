
#include <set>
#include <vector>
#include <iostream>

using namespace std;

void join(int x, int y, vector<int>& parents, vector<int>& counters);
int find(int x, vector<int>& parents);

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> counters(n + 1, 1);
    vector<int> parents(n + 1, -1);
    for (int i = 1; i <= n; i++) {
        parents[i] = i;
    }

    for (int i = 0; i < m; i++) {
        int size;
        cin >> size;

        int leader = -1;
        for (int j = 0; j < size; j++) {
            int member;
            cin >> member;
            if (leader != -1) {
                join(leader, member, parents, counters);
            } else {
                leader = member;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << counters[find(i, parents)] << ' ';
    }

    cout << '\n';
}


void join(int x, int y, vector<int>& parents, vector<int>& counters) {
    int a = find(x, parents);
    int b = find(y, parents);
    if (a != b) {
        parents[a] = b;
        counters[b] += counters[a];
    }
}


int find(int x, vector<int>& parents) {
    if (parents[x] == x) {
        return x;
    } else {
        int result = find(parents[x], parents);
        parents[x] = result;
        return parents[x];
    }
}