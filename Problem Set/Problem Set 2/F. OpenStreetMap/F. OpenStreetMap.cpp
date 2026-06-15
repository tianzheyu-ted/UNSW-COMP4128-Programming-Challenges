
#include <deque>
#include <vector>
#include <iostream>

using namespace std;


vector<long long> sliding_window_minimum(vector<long long>& numbers, int k);


int main() {
    int n, m, a, b;
    long long g_init, x, y, z; 
    cin >> n >> m >> a >> b >> g_init >> x >> y >> z;

    long long current_g = g_init;
    vector<vector<long long>> matrix(n, vector<long long>(m, 0));

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            matrix[r][c] = current_g;
            current_g = (current_g * x + y) % z;
        }
    }
   
    vector<vector<long long>> matrix_1(n, vector<long long>(m - b + 1, 0));
    for (int r = 0; r < n; r++) {
        matrix_1[r] = sliding_window_minimum(matrix[r], b);
    }

    vector<vector<long long>> matrix_2(n - a + 1, vector<long long>(m - b + 1, 0));
    for (int c = 0; c < m - b + 1; c++) {
        vector<long long> col(n, 0);
        for (int i = 0; i < n; i++) {
            col[i] = matrix_1[i][c];
        }

        vector<long long> col_min = sliding_window_minimum(col, a);
        
        for (int r = 0; r < n - a + 1; r++) {
            matrix_2[r][c] = col_min[r];
        }
    }

    long long result = 0;
    for (int i = 0; i < n - a + 1; i++) {
        for (int j = 0; j < m - b + 1; j++) {
            result += matrix_2[i][j];
        }
    }

    cout << result << '\n';
}



vector<long long> sliding_window_minimum(vector<long long>& numbers, int k) {
    deque<long long> dq;
    vector<long long> result;

    for (int i = 0; i < numbers.size(); i++) {
        if (!dq.empty() && dq.front() < i - k + 1) {
            dq.pop_front();
        }

        while (!dq.empty() && numbers[dq.back()] >= numbers[i]) {
            dq.pop_back();
        }

        dq.push_back(i);

        if (i >= k - 1) {
            result.push_back(numbers[dq.front()]);
        }
    }

    return result;
}