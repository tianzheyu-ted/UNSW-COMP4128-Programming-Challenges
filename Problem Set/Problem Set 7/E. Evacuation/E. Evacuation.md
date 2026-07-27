# Problem Set 7

## E. Evacuation

![](submission.png)


https://codeforces.com/submissions/tianzheyu#

### Process
Implemented a time expanded network utilizing Dinic's algorithm to model dynamic movement over time, combined with a preliminary BFS to calculate spatial constraints (gas spreading times).

### Challenges and Overcoming

1. When mapping my multi-dimensional states to 1D node IDs, I ran into a bug where my graph's edges were being improperly overwritten and misdirected. I found it when I reviewed my node index allocations and realized I used $n \times n \times t$ as the base offset for my super source, super sink, and rescue capsule nodes. This directly collided with the grid nodes at the final time step t (since time spans from 0 to t, it requires t+1 layers). Next time to prevent this bug, I will explicitly calculate the maximum possible size of the state space (e.g., $(t+1) \times n \times n$) and define a constant base offset strictly above this upper bound before assigning any special node IDs.

2. Later, when defining the valid movement edges, I ran into a bug where my program outputted a lower survivor count than expected on edge cases. I found it when I traced the timing of the gas spread and realized my movement condition `k < visited[target]` strictly prevented a scientist from reaching a capsule at the exact minute the gas arrived, even though the problem logic permits escaping in that final moment before infection. Next time to prevent this bug, I will manually diagram the exact boundary conditions of simultaneous events on a timeline to ensure my code's inequalities (< versus <=) perfectly reflect the problem's physical rules.