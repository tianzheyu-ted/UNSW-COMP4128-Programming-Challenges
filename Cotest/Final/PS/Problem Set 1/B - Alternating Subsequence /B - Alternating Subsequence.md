## B - Alternating Subsequence
### Process
Since the question is asking to find the maximum length alternating subsequence of the given sequence, a nature way of thinking this problem is to divide the orignal sequence to positive blocks and negitive block. Because our aim is an alternating subsequence, we can only chose one element from each blocks.

Besides, the question is asking to find the maximum length alternating subsequence with maximum sum, we just simplely need to choose the largest number from each block, and the result will naturely be the one we are looking for.

### Challenges and Overcoming
The implementation can be tricky for this question. During the process of traversing the numbers, I used a 'prev' varible to keep track of the previous number. Since a_i will never be 0, 0 can be an initial value for 'prev'. 

In each iteration, we can tell if the new value is in a new block by checking if current value have the same sign as 'prev'.

- If 'prev' and current value have the same sign, this means they are still in the same block. We just simplely need to update the biggest value in that blcok if the current value is larger.

- If 'prev' is 0 or do not share the same sign as current value, this means the previous block end, and we need to add the lagest value we stored for previous block into the result. After that we assign current value as the largest for the new block.

This solution successfully output the correct answer while keep the number of traverse needed 1, i.e. the time compleity is O(n).