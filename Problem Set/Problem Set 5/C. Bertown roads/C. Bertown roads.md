# Problem Set 5

## C. Bertown roads

![](submission.png)


https://codeforces.com/submissions/tianzheyu#


### Process
The question is asking to convert a undirected graph to directed graph while maintaining full graph reachability. According to Robbins' theorem, this orientation is possible if and only if the graph contains no bridges.

To solve this, I implemented a dfs based on Tarjan's bridge-finding algorithm. During the traversal, we maintain the discovery time (tin) and the lowest reachable time (low) for each node. As we traverse, tree edges are directed forward (from parent to child), and back edges are directed upward (from child to ancestor). If we evaluate a child node and find that low[child] > tin[parent], it means a bridge exists, and we immediately output 0.

### Challenges and Overcoming
The logical design of the algorithm was straightforward, but I encountered a severe issue during implementation. I accidentally passed the tin array by value instead of by reference in the DFS function signature (`vector<int> tin` instead of `vector<int>& tin`). Because of this missing ampersand, each recursive call operated on a local copy of the array.