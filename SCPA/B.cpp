
#include <vector>
#include <iostream>

using namespace std;

int main() {
    int r, c, k;
    cin >> r >> c >> k;

    vector<vector<char>> garden(r + 1, vector<char>(c + 1, ' '));
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            cin >> garden[i][j];
        }
    }

    
}