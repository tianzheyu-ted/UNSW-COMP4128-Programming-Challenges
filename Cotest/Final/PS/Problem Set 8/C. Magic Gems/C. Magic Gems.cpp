
#include <vector>
#include <iostream>

using namespace std;

static int MOD = 1e9 + 7;

typedef vector<vector<long long>> Matrix;

int main() {
    long long n; int m;
    cin >> n >> m;

    auto matrix_multiply = [&] (const Matrix& a, const Matrix& b) -> Matrix {
        int r = a.size();
        int c = b[0].size();
        int k = a[0].size();
        Matrix res(r, vector<long long>(c, 0));
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                for (int p = 0; p < k; ++p) {
                    res[i][j] = (res[i][j] + a[i][p] * b[p][j]) % MOD;
                }
            }
        }
        return res;
    };

    auto matrix_power = [&] (Matrix base, long long n) -> Matrix {
        int m = base.size();
        Matrix res(m, vector<long long>(m, 0));
        for (int i = 0; i < m; ++i) {
            res[i][i] = 1; 
        }
        while (n > 0) {
            if (n & 1) {
                res = matrix_multiply(res, base);
            }
            base = matrix_multiply(base, base);
            n >>= 1;
        }
        return res;
    };

    vector<vector<long long>> T(m, vector<long long>(m, 0));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            if (i == 0) {
                if (j == 0 || j == m - 1) {
                    T[i][j] = 1;
                }
            } else {
                if (j == i - 1) {
                    T[i][j] = 1;
                }
            }
        }
    }

    Matrix result_matrix = matrix_power(T, n - m + 1);
    long long result = 0;
    for (auto num : result_matrix[0]) {
        result += num;
        result %= MOD;
    }

    cout << result << '\n';
}