
#include <set>
#include <vector>
#include <iostream>

using namespace std;

void join(int x, int y, vector<int>& parents);
int find(int x, vector<int>& parents);

int main() {
    int n;
    cin >> n;

    vector<int> parents(26, -1);
    for (int i = 0; i < 26; i++) {
        parents[i] = i;
    }

    set<int> appeared;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;

        int leader = s[0] - 'a';
        appeared.insert(leader);

        for (int j = 1; j < s.size(); j++) {
            appeared.insert(s[j] - 'a');
            join(leader, s[j] - 'a', parents);
        }
    }

    set<int> counter;
    for (int i = 0; i < 26; i++) {
        counter.insert(find(i, parents));
    }

    cout << counter.size() - (26 - appeared.size()) << '\n';
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
        int parent = find(parents[x], parents);
        parents[x] = parent;
        return parent;
    }
}