
#include <stack>
#include <vector>
#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<long long> heights(n + 1, 0);
    for (int i = 0; i < n; i++) {
        cin >> heights[i];
    }

    stack<int> stack;
    long long max_area = 0;

    for (int i = 0; i < n + 1; i++) {
        while (!stack.empty() && heights[i] < heights[stack.top()]) {
            auto height = heights[stack.top()];
            stack.pop();

            int w;
            if (stack.empty()) {
                w = i;
            } else {
                w = i - stack.top() - 1;
            }

            max_area = max(max_area, height * w);
        }
        stack.push(i);
    }

    cout << max_area << '\n';
}