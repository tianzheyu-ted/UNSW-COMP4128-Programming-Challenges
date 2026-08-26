
#include <vector>
#include <iostream>

using namespace std;

int main() {

    // 传入上限 N，返回一个包含所有小于等于 N 的素数的 vector
    auto get_primes = [](long long N) -> vector<long long> {
        vector<long long> primes;
        vector<long long> lpf(N + 1, 0); 
        for (long long i = 2; i <= N; i++) {
            if (lpf[i] == 0) { // 如果没被标记过，说明是素数
                lpf[i] = i;
                primes.push_back(i);
                // 从 i*i 开始标记 i 的倍数，防止重复工作
                for (long long j = i * i; j <= N; j += i) {
                    if (lpf[j] == 0) lpf[j] = i;
                }
            }
        }
        return primes; 
        // 提示：考场上如果需要在外部用到 lpf 数组，可以让 lambda 返回 std::pair<vector, vector> 
        // 或者直接按引用捕获一个在外部声明好的 lpf 数组。
    };

    long long n;
    cin >> n;

    for (auto& prime : get_primes(n)) {
        cout << prime << ' ';
    }
    
    cout << '\n';
}