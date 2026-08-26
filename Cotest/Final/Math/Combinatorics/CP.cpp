#include <vector>

using namespace std;

long long MOD = 1000000007;
int MAX_N = 200000; // 根据题目要求的最大 n 调整

// 预定义数组，放在全局或 main 函数开头
vector<long long> fact(MAX_N + 1);
vector<long long> invfact(MAX_N + 1);

// 前置工具：快速幂
auto fast_pow = [](long long a, long long n) {
    long long res = 1;
    a %= MOD;
    while (n > 0) {
        if (n % 2 == 1) res = (res * a) % MOD;
        a = (a * a) % MOD;
        n /= 2;
    }
    return res;
};

// 1. O(N) 预处理阶乘与逆元
auto init_combinatorics = [&]() {
    fact[0] = 1;
    invfact[0] = 1;
    
    // 递推求阶乘
    for (int i = 1; i <= MAX_N; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    
    // 费马小定理求出最大阶乘的逆元
    invfact[MAX_N] = fast_pow(fact[MAX_N], MOD - 2);
    
    // 核心优化：倒推求其余逆元，公式为 (i-1)!^-1 = i!^-1 * i
    for (int i = MAX_N - 1; i >= 1; i--) {
        invfact[i] = (invfact[i + 1] * (i + 1)) % MOD;
    }
};

// 2. 组合数 C(n, k)
// 公式: n! / (k! * (n-k)!)
auto nCr = [&](int n, int k) -> long long {
    if (k < 0 || k > n) return 0; // 防御性编程，处理越界查询
    // 对应公式: fact[n] * invfact[k] * invfact[n-k] % MOD
    return fact[n] * invfact[k] % MOD * invfact[n - k] % MOD;
};

// 3. 排列数 P(n, k) 或称为 A(n, k)
// 公式: n! / (n-k)!
auto nPr = [&](int n, int k) -> long long {
    if (k < 0 || k > n) return 0;
    return fact[n] * invfact[n - k] % MOD;
};