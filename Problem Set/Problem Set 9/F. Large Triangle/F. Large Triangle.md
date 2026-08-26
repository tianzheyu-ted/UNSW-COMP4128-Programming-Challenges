# Problem Set 9

## E. Point Ordering

![](submission.jpg)

### Process
I implemented an $O(n^2 \log n)$ approach using a rotational sweep-line. I generated all possible base edges, sorted them by polar angle, and used binary search on a dynamically maintained permutation array to find the third vertex that matches the target area.

### Challenges and Overcoming
When maintaining the monotonic property of the points during the angular sweep, I ran into a bug where I accidentally swapped the actual `Point` objects in the main coordinate array instead of swapping their reference indices in the `cur_order` tracking array. I found it when I printed out the coordinates during the binary search step and noticed the structural integrity of my original point set was completely corrupted. Next time to prevent this bug, I will enforce strict separation between physical data and logical permutations by explicitly adding `const` modifiers to the base data vector, ensuring it remains read-only during the sweep line process.
