# Problem Set 7

## A. Cops And Robbers

![](submission.png)


https://codeforces.com/submissions/tianzheyu#

### Process
Constructed a flow network with node capacities by splitting grid cells into in and out nodes to represent the barricade costs. Added a super sink for the grid boundaries and ran Dinic's algorithm to find the minimum cut.

### Challenges and Overcoming
When coding the boundary check to connect edge cells to the super sink, I ran into a compilation bug stating: "expression must be a modifiable lvalue". I found it when the compiler highlighted my conditional statement: `if (i == 0 || j == 0 || i = m - 1 || j == n - 1)`. I had accidentally used `=` instead of `==` for the row boundary check. Because logical `||` has higher precedence than `=`, the compiler tried to assign the value `m - 1` to the boolean result of the earlier conditions, which is an rvalue. Next time to prevent this from happenning, I will pay extra care for the condition statements.

