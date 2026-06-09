# Problem Diary for Problem Set 1

## A - Duff and Meat
### Process
The question is asking to minimized the money needed to buy meat. Since we are allow to keep the meat we perivously bought to meet her future requirement, the nature thought is to buy all the meat needed in the day when the price is lowest. So we can sort the price, and try to buy all the meat in that day.

### Challenges and Overcoming
However, for example there are day1 and day2, and the price of meat in day2 is lower than day1, in this case we can not buy meat in day2 to meet the requirement in day1. This tells us we can only buy the meat to satisfy dayX's requirement in the lowest price day that before dayX.


This means when we are traversing all the day, we need to somehow know the lowest price day before it. The naive way is to traverse all the day before it to get the lowest price, however we can do better by keeping the lowest price before that day and update it if the current price is lower. This reduce the time complexity from O(n^2) to O(n).



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


## C - Books
### Process
The question gives a sequence of estimated time that the boy need to read those books. And the question gives the free time the person has. The output should be the maximum number of book he can read in the order of the sequence.

Since the person will always reading in that order, we can maintain a sliding window, i.e. if the time left is lager than the time needed for the next book, we will add the book into the windows, if not then we will try to remove the book in the front of the window to add the time left back and possiblely have the enough time to read the next book.

### Challenges and Overcoming
The thing I forgot and debug is that after finishing travsing all books, I still need to update the max window size if the current windows size is larger.


## D - Quests
### Process
The question is saying that there are n quests provided, and there d days to do these quests. We can get coins after finish one quests, and the number of coins we want to achieve(c) is also provided. The question wants us to find the maximum gap for the person to do the same quests but still achieve c coins.

Firstly, it is obvious that if there is a quest that already has a reward larger than c, we can just simplely do that in the first day and achieve the goal of having c coins no matter how large the gap can be. So this case will just output 'Infinity'.

Secondly, let's pretend the gap is 0, and we choose to do the largest reward quests for every day (n days in total). This is the maximum coins we can get. If this is still less than c, no matter what we do, there is no way we can have reward as c. This case we can just return 'Impossible'.

Now is the tricky part, in my orignal solution I was trying to caculate the lagest gap k directly by going though all days. 


### Challenges and Overcoming
Now is the tricky part, in my orignal solution I was trying to caculate the lagest gap k directly by going though all days. But I shouldn't do this beacuse it way more easy to check whether a given k can lead to getting reward coins larger than c rather than trying to caculate myself. Additionly, there is no point to have a k larger than n because if k is larger than n, every quests will be done at most once already, and this allows k to be infinity, just like the I perviously discussed about. And clearly, k can not be less than 0, which means k is a value in between 0 and n - 1 if the pervious 2 cases is not happenning.

Therefore, instead of trying to use 
``` cpp
int k = 0;
int current_coin_gain = 0;
for (int j = 0; j < d; j++) {
    ...
}
```
to directly calculate k, we can use Binary Search to search for each value in between 0 and n - 1.

To do that we still need a helper function to check if with gap k we can achieve c coins as rewards.

```cpp
bool check_k(int k, int d, long long c, vector<long long>& rewards) {
    long long coins = 0;
    for (int i = 0; i < d; i++) {
        int current_day_in_cycle = i % (k + 1);
        if (current_day_in_cycle < rewards.size()) {
            coins += rewards[current_day_in_cycle];
        }
        if (coins >= c) return true;
    }
    return coins >= c;
}
```
The main logic of this function is to check if the maximum rewards we can gain with gap length k is larger than c. Clearly, in order to compute the maximum reward gain, we need to do as much and high-reward quests as we can. 
Firstly, rewards already sorted in decreasing order. And we will keep doing the most valueable quests in a period of k, and in between do those less valueable quests. 



## E - Riverside Curio
### Process
The question said a person is marking each day's water level. He only marks the water level if there is no old water level in the same position. And he will record the number of marks strictly above the current day's water level.

The question aimed to find the minimum possible sum of the number of marks strictly below the water level among all days.


### Challenges and Overcoming
In the start, I have no idea of how to do this question, especially how to get the number of marks strictly below the water level in each day. 

After getting some hits, because what we know is the number of marks above the water level, in order to get the number of marks strictly below the water level, we need to find something that links number of marks above and below together. A nature way of thing that is linking them by the number of total marks for each day.

Clearly, without the constrain of the person only marks the water level if there is no old water level in the same position, the number of total marks is just the number of days. However, since we have the constrain, the rule we have will be: Total[i - 1] <= Total[i] <= Total[i - 1] + 1. Besides, since we know there are Above[i] marks plus current water level for sure, there is Total[i] >= Above[i] + 1.

And clearly, Total[i] = Above[i] + Below[i] + 1 => Below[i] = Total[i] - Above[i] - 1.

Another challenge is you can not make every constrian for Total satisfy in one loop.
```cpp
for (int i = 1; i < n; i++) {
    int prev = total[i - 1];
    int curr_and_above = m[i] + 1;
    total[i] = max(prev, curr_and_above);
}

for (int i = n - 2; i >= 0; i--) {
    total[i] = max(total[i + 1] - 1, total[i]);
}
```
We have to check if the previous day's total mark can have a result as today's mark, since we can only add 1 mark more in one day.

The rest is easy, just use Below[i] = Total[i] - Above[i] - 1 to calculate the sum of the number of marks strictly below the water.


## F - The Fair Nut and Strings
### Process
Description of the Question

1. every string is build by 'a' or 'b',
2. every string's length is n,
3. there is k strings in total,
4. all the string s are in between s and t in dictionary order.
5. define c as the number of all possible prefix of all k strings
6. the aim is to find largest c.


### Challenges and Overcoming
After getting the hint, I know I have to transform this string question to a Trie problem since there are only 2 direction of generate new valid string, i.e. adding 'a' or adding 'b'. Therefore, we can construct a Trie in the following way:

1. the root node represent the empty string,
2. for each char in the string, if it is 'a', we go to the left child node, if it is 'b', we go to the right child node. 


After doing this, what the question provide is 2 paths in the Trie, and we need to search for k possible paths in between these 2 paths and in the same time maximum the number of nodes those paths can cover. This is due to each node in the Trie is represent a possible prefix.


In order to maximum the number of nodes we cover, we can use greedy method, i.e. in each level of the Trie, we try to cover as many nodes as possible. However, to cover the nodes we have 2 constrians:

1. since we only have k paths to cover nodes, and in each level each path can only cover at most 1 node, we can only cover k nodes in each level.
2. we can only cover the node in between s and t.

Now the question is how to caculate how many nodes in each level that are i between s and t. We can consider s and t as a binary number ('a' -> 0, 'b' -> 1). Suppose in level i - 1, the number of nodes between s and t is diff + 1, then in the next level i, these diff nodes in the pervious level will have their child nodes, leading to 2 * (diff + 1) nodes in this level. However, we don't know for sure that the child nodes of left-most and right-most node in previous level are in the range.

Suppose in i - 1 level, the binary value of t is T_i-1 and s is S_i-1. The prev_diff = T_i-1 - S_i-1. In this level, T_i = 2 * T_i-1 + T[i], S_i = 2 * S_i-1 + S[i]. The diff = 2 * T_i-1 + T[i] - (2 * S_i-1 + S[i]) = 2 * (T_i-1 - S_i-1) + T[i] - S[i]. Therefore the number of nodes in between s and t i level i is 2 * (T_i-1 - S_i-1) + T[i] - S[i] + 1.

Accoding to above 2 constrain, if the maximum number of nodes we cover in level i is max(k, 2 * (T_i-1 - S_i-1) + T[i] - S[i] + 1).