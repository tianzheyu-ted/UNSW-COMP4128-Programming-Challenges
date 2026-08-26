
#include <vector>
#include <iostream>

using namespace std;

vector<vector<long long>> typedef Matrix;
long long MOD = 1000000007;

int main() {
    // 1. 矩阵乘法 Lambda
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

    // 2. 矩阵快速幂 Lambda
    auto mat_pow = [&](Matrix A, long long p) {
        int n = A.size();
        Matrix res(n, std::vector<long long>(n, 0));
        // 初始化为单位矩阵 (主对角线为1，相当于普通乘法里的初始值 1)
        for (int i = 0; i < n; ++i) res[i][i] = 1; 
        
        while (p > 0) {
            if (p % 2 == 1) res = mat_mul(res, A);
            A = mat_mul(A, A);
            p /= 2;
        }
        return res;
    };

    // 求解线性递推数列的第 n 项 (n 从 0 开始)
    // init_vals: 初始项 [a_{k-1}, a_{k-2}, ..., a_0] (必须按这个倒序传入)
    // coeffs: 递推系数 [c_1, c_2, ..., c_k]
    auto solve_recurrence = [&](const vector<long long>& init_vals, const vector<long long>& coeffs, long long n) -> long long {
        int k = coeffs.size();
        
        // 如果求的项在初始值范围内，直接返回
        if (n < k) {
            return init_vals[k - 1 - n]; 
        }
        
        // 构造转移矩阵 T
        Matrix T(k, vector<long long>(k, 0));
        
        // 矩阵的第一行填入系数
        for (int i = 0; i < k; ++i) {
            T[0][i] = coeffs[i]; 
        }
        // 矩阵的次对角线填入 1 (实现状态的平移)
        for (int i = 1; i < k; ++i) {
            T[i][i - 1] = 1; 
        }
        
        // 因为 init_vals 包含了 k 项，我们要推进到第 n 项，需要乘 T 的 (n - k + 1) 次方
        Matrix T_n = mat_pow(T, n - k + 1);
        
        // 计算目标值 (T_n 的第一行 乘以 初始值列向量)
        long long ans = 0;
        for (int i = 0; i < k; ++i) {
            ans = (ans + T_n[0][i] * init_vals[i]) % MOD;
        }
        
        return ans;
    };
}