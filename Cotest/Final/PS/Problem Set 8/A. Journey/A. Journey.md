
# Problem Set 8

## A. Journey

![](submission.png)

### Process
Derived the state transition equation for the expected number of steps using Expected DP. After realizing my initial formula missed the self-loop (staying in the same state), I re-calculated the math to arrive at the correct algebraic representation: $dp[i] = \frac{1}{1 - \frac{i}{N}} \times \left( \frac{N-i}{N}(dp[i+1] + 1) + \frac{i}{N} \right).$


### Challenges and Overcoming
When coding my expected DP logic, I ran into a bug where my program consistently output `0`, despite my mathematical formula being correct on paper. 

I found it when I printed out the intermediate fraction values like `i / n` and saw they were all evaluating to `0`. Because I declared `i` and `n` as integers, C++ was performing integer division (downward truncation). Next time to prevent this bug, I will explicitly cast variables to doubles (e.g., `(double)i / n`) during calculations, or read variables like `n` as a `double` from the start when solving expectation problems.

I also ran into an issue where the default `cout` output format did not provide enough decimal places, risking a precision error. Next time to prevent this bug, I will always include `<iomanip>` and configure `cout << fixed << setprecision(10)` to ensure my floating-point output meets strict judge requirements.