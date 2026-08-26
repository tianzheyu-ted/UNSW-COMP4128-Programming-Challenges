
# Problem Set 8

## B. Math

![](submission.png)


### Process
To solve this problem, I used prime factorization to break down the initial number. The minimum possible value is the product of all unique prime factors. To find the minimum number of operations, I tracked the maximum exponent among all prime factors. I then used bitwise shifts to find the smallest power of 2 that is greater than or equal to this maximum exponent to calculate the `sqrt` operations, adding one `mul` operation if the initial exponents were not perfectly aligned.

### Challenges and Overcoming
When coding the loop to find the required power of 2, I ran into a bug where my program caused an infinite loop. I wrote the condition backwards as `while (maximum_power < (1 << second_power))`. I found it when my code wouldn't terminate; because `second_power` was increasing, the right side kept growing and the condition was always true. Next time to prevent this bug, I'll manually trace the first two iterations of my `while` loops to ensure the termination condition is actually reachable.

I also ran into a logical error where I printed out the wrong variable. I was outputting the target exponent value itself by writing `cout << (1 << second_power) + 1` instead of the actual number of `sqrt` operations, which was simply `second_power + 1`. I found it when my output was significantly larger than the test cases expected. Going forwards, I will double-check the specific values the problem statement asks for before writing my `cout` statements. 

Finally, I got stuck on an edge case because I initialized `int second_power = 1`. This failed for numbers where the maximum prime exponent was already 1, which requires 0 operations. I found it when testing smaller numbers. Next time to prevent this, I will test base edge cases (e.g. n=2) locally to verify my initial state variables before submitting.

