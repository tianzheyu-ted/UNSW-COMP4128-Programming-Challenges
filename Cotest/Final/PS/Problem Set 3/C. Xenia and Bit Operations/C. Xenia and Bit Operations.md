
# Problem Set 3

## A. The Problem Set

![](submission.png)

### Process
The question provides 2^n non-negative integers, and tells us how to calculate v: the first iteration, the result is bit-wise OR of adjacent elements of sequence a. At the second iteration, the result is the bitwise exclusive OR of adjacent elements of the sequence obtained after the first iteration.

### Challenges and Overcoming
Since in each level they will only calculate adjacent elements from the previous level, it is perfect to use range tree. And each time we update one value, we recursively update all value in tree that affect by this, i.e. the path from that leaf node to the root node. And this can be done in O(log (2^n)). And for the result v, it is just simplely the value in root node.

There is a question about how to switch between XOR and OR, I used a hight value in each node that record the current height. Clearly, when the current height is odd, we will preform OR, and if it is even, we will preform XOR. And since update only change the value instead of tree structure, it only takes O(2^n).