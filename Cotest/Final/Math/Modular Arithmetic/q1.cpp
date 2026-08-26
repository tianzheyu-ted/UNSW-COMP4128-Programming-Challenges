

#include <iostream>
#include <vector>

using namespace std;

/**
 *  例题 1：带负数和除法的综合计算
    题目描述：给定 x、y、z，求式子  
    ((x−y) / z) (mod 10^9 + 7) 的值
    已知 z 与 10^9 +7 互质，且 x 可能小于 y。
 */

long long MOD = 1e9 + 7;

long long sub_mod(long long a, long long b, long long m) {
    return ((a - b) % m + m) % m; 
}

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

long long modular_inverse(long long a, long long m) {
    return fast_pow(a, m - 2, m);
}

int main() {
    long long x, y ,z;
    cin >> x >> y >> z;
    cout << (sub_mod(x, y, MOD) * modular_inverse(z, MOD)) % MOD << '\n';
}