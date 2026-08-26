
#include <iostream>
#include <vector>

using namespace std;

/**
 *  1. 快速幂 (Fast Exponentiation)
    用途：在 O(logn) 时间内求出 a^n (mod m)。
    原理：分治思想。
    如果 n 是偶数，a^n = a^(n/2) x a^(n/2)
    如果是奇数，再多乘一个 a。
 */

long long fast_pow(long long a, long long n, long long m) {
    long long res = 1;
    a = a % m;
    while (n > 0) {
        if (n % 2 == 1) res = (res * a) % m; // 奇数时，乘入结果
        a = (a * a) % m;                     // 偶数时，底数平方
        n /= 2;
    }
    return res;
}

/**
 *  2. 模逆元 (Modular Inverse)
    用途：实现模意义下的“除法”。求解使得 a ⋅ a^{−1} ≡ 1(mod m) 的 a^{−1}
    最常用方法（费马小定理）：当模数 m 是质数（绝大数题目都是）时，
    根据 a^{m−1} ≡ 1(mod m)，可得 a^{−1} ≡ a^{m−2} (mod m)。
    实现：直接复用上面的快速幂！逆元就是 fast_pow(a, m - 2, m)。
 */
long long modular_inverse(long long a, long long m) {
    return fast_pow(a, m - 2, m);
}