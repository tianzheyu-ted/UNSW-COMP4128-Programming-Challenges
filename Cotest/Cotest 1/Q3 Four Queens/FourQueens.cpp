
#include <set>
#include <vector>
#include <iostream>

using namespace std;

int main() {

    const int direction_row[] = {-1, 1, 0, 0, -1, -1, 1, 1};
    const int direction_col[] = {0, 0, 1, -1, -1, 1, 1, -1};
    const char row_convert[] = {'8', '7', '6', '5', '4', '3', '2', '1'};
    const char col_convert[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

    vector<vector<bool>> marked_chessboard(8, vector<bool>(8, false));

    for (int i = 0; i < 8; i++) {
        string row;
        cin >> row;
        for (int j = 0; j < 8; j++) {
            if (row[j] == '*') marked_chessboard[i][j] = true;
        }
    }
    
    bool first = true;
    long long arrangements_num = 0;
    vector<pair<int, int>> record_queens;

    for (int i = 0; i < 64; i++) {
        for (int j = i + 1; j < 64; j++) {
            for (int k = j + 1; k < 64; k++) {
                for (int l = k + 1; l < 64; l++) {
                    vector<vector<bool>> chessboard(8, vector<bool>(8, false));

                    vector<pair<int, int>> queens = {
                        {i / 8, i % 8},
                        {j / 8, j % 8},
                        {k / 8, k % 8},
                        {l / 8, l % 8}
                    };

                    set<pair<int, int>> s(queens.begin(), queens.end());

                    for (auto queen : queens) {
                        chessboard[queen.first][queen.second] = true;
                        for (int dir = 0; dir < 8; dir++) {
                            pair<int, int> curr_pos = queen;
                            while (true) {
                                curr_pos.first += direction_row[dir];
                                curr_pos.second += direction_col[dir];

                                if (
                                    s.count(curr_pos) == 1
                                    || curr_pos.first < 0
                                    || curr_pos.first >= 8
                                    || curr_pos.second < 0
                                    || curr_pos.second >= 8
                                ) break;

                                chessboard[curr_pos.first][curr_pos.second] = true;
                            }
                        }
                    }

                    bool valid = true;
                    for (int r = 0; r < 8; r++) {
                        for (int c = 0; c < 8; c++) {
                            if (marked_chessboard[r][c] && !chessboard[r][c]) {
                                valid = false;
                                break;
                            }
                        }
                        if (!valid) break;
                    }

                    if (valid) {
                        arrangements_num++;
                        if (first) {
                            record_queens = queens;
                            first = false;
                        }
                    }
                }
            }
        }
    }

    cout << arrangements_num << '\n';

    if (arrangements_num > 0) {
        for (auto queen : record_queens) {
            cout << col_convert[queen.second] << row_convert[queen.first] << '\n';
        }
    }
}