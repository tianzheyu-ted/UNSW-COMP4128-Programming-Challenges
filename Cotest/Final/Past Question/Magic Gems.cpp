
#include <vector>
#include <iomanip>
#include <iostream>

using namespace std;

vector<vector<long long>> typedef Matrix;
long long MOD = 1000000007;

int main() {
    long long n, m;
    cin >> n >> m;

    auto mat_mul = [&](const Matrix& A, const Matrix& B) {
        int r = A.size(), k = A[0].size(), c = B[0].size();
        Matrix res(r, std::vector<long long>(c, 0));
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                for (int l = 0; l < k; ++l) {
                    res[i][j] = (res[i][j] + A[i][l] * B[l][j]) % MOD;
                }
            }
        }
        return res;
    };

    auto mat_pow = [&](Matrix A, long long p) {
        int n = A.size();
        Matrix res(n, std::vector<long long>(n, 0));
        for (int i = 0; i < n; ++i) res[i][i] = 1; 
        while (p > 0) {
            if (p % 2 == 1) res = mat_mul(res, A);
            A = mat_mul(A, A);
            p /= 2;
        }
        return res;
    };

    Matrix A(m, vector<long long>(m, 0));
    for (int i = 0; i < m; i++) {
        if (i == 0) {
            A[i][0] = 1;
            A[i][m - 1] = 1;
        } else {
            A[i][i - 1] = 1;
        }
    }

    long long p = n - m + 1;
    Matrix Trans = mat_pow(A, p);

    long long ans = 0;
    for (int j = 0; j < m; ++j) {
        ans = (ans + Trans[0][j]) % MOD;
    }

    cout << ans << '\n';
}