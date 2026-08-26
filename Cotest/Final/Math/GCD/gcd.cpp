
#include <vector>
#include <numeric>
#include <iostream>

using namespace std;

int main() {
    // 1. 求最大公约数 (GCD)
    auto gcd = [](auto& self, long long a, long long b) -> long long {
        return b == 0 ? a : self(self, b, a % b);
    };

    // 2. 求最小公倍数 (LCM) - 防溢出写法
    auto lcm = [&](long long a, long long b) -> long long {
        if (a == 0 || b == 0) return 0;
        // 先除以 gcd 再乘，避免 a * b 直接爆 long long
        return (a / gcd(gcd, a, b)) * b; 
    };

    // 扩展欧几里得算法 (exGCD)
    // 返回值是 gcd(a, b)，同时通过引用修改传入的 x 和 y
    auto exgcd = [](auto& self, long long a, long long b, long long& x, long long& y) -> long long {
        if (b == 0) {
            x = 1; 
            y = 0;
            return a;
        }
        long long x1, y1;
        long long d = self(self, b, a % b, x1, y1);
        x = y1;
        y = x1 - (a / b) * y1;
        return d;
    };

    // 一键求解线性同余方程 (ax ≡ c mod m)
    // 求解方程 ax ≡ c (mod m)
    // 如果有解，返回最小正整数解 x；如果无解，返回 -1
    // 遇到“求逆元”但模数 m 不是质数时，不能用费马小定理怎么办？
    // 破解：求 a 在模 m 下的逆元，等价于解同余方程 ax ≡ 1 (mod m)。你直接调用 solve_linear_congruence(a, 1, m) 就能秒杀！
    auto solve_linear_congruence = [&](long long a, long long c, long long m) -> long long {
        long long x, y;
        // 先求出 ax + my = gcd(a, m) 的解
        long long d = exgcd(exgcd, a, m, x, y);
        
        // 贝祖定理：如果 c 不能被 gcd(a, m) 整除，则方程无解
        if (c % d != 0) {
            return -1; // 代表无解
        }
        
        // 将特解按比例放大 (c / d) 倍
        long long target_x = x * (c / d);
        
        // 模数在方程缩放后会变成 m / d
        long long mod_new = m / d;
        
        // 用最经典的取模大法，将 target_x 转换到 [0, mod_new - 1] 的最小正整数解
        return ((target_x % mod_new) + mod_new) % mod_new;
    };


    // 扩展中国剩余定理（EXCRT）
    // 依赖前文的 exgcd 函数
    // 参数: a 存放余数集, m 存放模数集。方程组格式为 x ≡ a[i] (mod m[i])
    // 返回: 满足所有方程的最小正整数解 x。如果方程组相互矛盾无解，返回 -1。
    auto excrt = [&](const vector<long long>& a, const vector<long long>& m) -> long long {
        int n = a.size();
        long long current_x = a[0];
        long long current_m = m[0];

        for (int i = 1; i < n; i++) {
            long long A = current_m;
            long long B = m[i];
            
            // 目标等式: A * k1 - B * k2 = a[i] - current_x
            // 令 C = a[i] - current_x，并在取模意义下转为正数防错
            long long C = ((a[i] - current_x) % B + B) % B; 

            long long k1, k2;
            long long d = exgcd(exgcd, A, B, k1, k2);

            // 如果 C 不能被 gcd(A, B) 整除，说明方程相互矛盾，无解
            if (C % d != 0) return -1; 

            // 求解当前的步长乘数 k1，并将其缩小到最小正整数范围内防溢出
            long long step = B / d;
            k1 = (k1 % step + step) % step; 
            
            // 注意：k1 * (C / d) 可能会很大，这里运用取模性质防止溢出
            // C++ 中的直接相乘可能会爆 long long，保险起见可以用 __int128 强转一下
            k1 = ((__int128)k1 * (C / d)) % step; 

            // 合并方程，更新当前的解与模数
            current_x = current_x + k1 * current_m;
            current_m = current_m * step; // 更新为 lcm(current_m, B)
            
            // 保证 current_x 始终落在有效正数区间
            current_x = (current_x % current_m + current_m) % current_m;
        }
        
        return current_x;
    };
}