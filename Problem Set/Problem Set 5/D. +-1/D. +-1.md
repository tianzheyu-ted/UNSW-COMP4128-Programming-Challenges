# Problem Set 5

## D. +-1

![](submission.png)


https://codeforces.com/submissions/tianzheyu#


### Process
The problem presents a 3 x N grid where we need to choose the signs of variables such that after sorting each column independently, the middle row consists entirely of 1s. Since sorting a column of three 1s and -1s places the median in the middle, the condition simplifies to: every column must contain at least two 1s. For a column with elements X, Y, Z, this is the same as saying ((X or Y) and (Y or Z) and (X or Z)). The entire problem can be modeled as a standard 2-SAT (2-Satisfiability) problem.


### Challenges and Overcoming

My initial approach was a greedy strategy, attempting to deduce the signs based solely on the original middle row horizontally. I quickly realized this was a fatal misunderstanding of the problem—the variables are highly interdependent globally, and a local greedy choice on a free variable can easily lock the system into a contradiction later on. 

After pivoting to build a 2-SAT implication graph and using Kosaraju's algorithm to find SCCs, the real challenge shifted to implementation details.

1. I initially forgot to explicitly build the reversed graph (`rev_adj`), which is the core requirement for Kosaraju's second DFS part.

2. I accidentally reused the first pass's `visited` array(already full of true) inside the second DFS.
