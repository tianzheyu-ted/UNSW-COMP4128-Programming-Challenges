

#include <vector>
#include <iostream>

using namespace std;

int MAX_N = 1e8;

/**
 *  考场一秒决策树
    第一步看 n：只要最大数字 n > 1e7，无脑选 factorize_single（因为 LPF 数组根本存不下）。
    第二步看 Q：如果 n <= 1e7 且查询次数 Q 很大，花点时间写个预处理，果断选 factorize_fast 享受秒杀快感。
 */

int main() {
    /**
     *  factorize_single (暴力枚举到根号 n)
        核心策略：直接硬算，主打省空间。
        适用场景：低频查询，但数值极大（数字个数少，但数字本身非常大）。
        数据特征：查询次数少（甚至只有几次），数字 n 可高达 10^14。
        复杂度：单次查询时间 O(sqrt(n))。空间复杂度 O(1)。  
        致命限制：受限于时间（如 1秒 = 10^8 次运算）。只要 n <= 10^14，循环次数就在 1e7 内，
        绝对安全。但如果 n 达到 10^18，就会导致 TLE（超时）
     */
    auto factorize_single = [](long long n) -> vector<pair<long long, int>> {
        vector<pair<long long, int>> factors;
        for (long long i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                int counter = 0;
                while (n % i == 0) {
                    counter++;
                    n = n / i;
                }
                factors.push_back({i, counter});
            }
        }
        if (n > 1) {
            factors.push_back({n, 1});
        }
        return factors;
    };

    auto build_lpf = [](int N) {
        vector<int> lpf(N + 1);
        for (int i = 2; i <= N; i++) {
            lpf[i] = i; 
        }
        for (int i = 2; i * i <= N; i++) {
            if (lpf[i] == i) {
                for (int j = i * i; j <= N; j += i) {
                    if (lpf[j] == j) {
                        lpf[j] = i; 
                    }
                }
            }
        }
        return lpf;
    };

    /**
     *  factorize_fast (基于 LPF 筛法)
        核心策略：空间换时间。
        适用场景：高频查询，且数值范围较小（数字个数多，但数字本身不大）。
        数据特征：数字上限 N <= 10^7，查询次数 Q >= 10^4。
        复杂度：预处理时间 O(N log log N)，单次查询时间 O(log n)。空间复杂度 O(N)。  
        致命限制：受限于内存（如 256MB），LPF 数组最大只能开到 1e7 到 2e7。如果强行开更大，
        会导致 MLE（内存超限）
     */
    auto factorize_fast = [](int x, const vector<int>& lpf) -> vector<pair<int, int>> {
        vector<pair<int, int>> factors;
        while (x > 1) {
            int p = lpf[x];
            int counter = 0;
            while (x % p == 0) {
                counter++;
                x /= p;
            }
            factors.push_back({p, counter});
        }
        return factors;
    };

    auto lpf = build_lpf(MAX_N);

    int n;
    cin >> n;

    for (auto& factor : factorize_fast(n, lpf)) {
        cout << factor.first << ': ' << factor.second << '\n';
    }

    cout << '\n';
}