# Problem Set 7

## D. Delivery Bears

![](submission.png)


https://codeforces.com/submissions/tianzheyu#

### Process
Implemented a floating point binary search combined with Dinic's algorithm to evaluate the maximum uniform weight discrete entities could carry across a directed graph.

### Challenges and Overcoming
When coding my solution, I ran into a bug where I attempted to calculate the maximum flow just once on the original graph and divide the result using standard integer variables. I found it when I realized my logic couldn't handle fractional weights, and standard max flow cannot inherently force flow to be divided uniformly across a specific number of distinct paths. Next time to prevent this bug, when a flow problem requires uniform distribution across discrete entities, I will immediately structure my code to use a binary search and explicitly write a check function that rebuilds the flow network from scratch for each floating point iteration, dynamically converting the weights into discrete capacities.