
# Problem Set 2

## A. Secret Passwords

![](submission.png)

### Process
The question is saying that 2 passwords are equivalent if there is a letter in both poth passwords or there is another password that these 2 passwords are both equivalent to. And the question provides n passwords, and ask us to return the minimal number of passwords that guaranteed to access the system.

My initial thought was using binary search, since the the number of passwords needed to access all system is in between 1 and n. However, in the check function, it is difficult to tell if x passwords can guaranteed to access the system. The way is to traverse all possible combinations of x passwords which is not efficent enougth.



### Challenges and Overcoming
After getting some hints, I know we can represnt this question in graph. Since we only have 26 letters in total, and every passwords is made from those 26 letters, every password must be equivalent to some of these 26 letters. Since there are equivalent, knowing one of the letter will have a result that knowing every passwords that equivalent to it. In the graph representation, this is to find the number of equivalent class in that graph, i.e. number of connected components. And we can ignore those letters doesn't even appear in any passwords.

So the logic is, we have 26 nodes represente 26 letters in the graph. For every passwords, we link every pair of letters that appeared in this passwords, (this means this password makes this 2 letters equivalent). After constructing the graph, we perform a stander way of finding the number of connected components i.e. try to start each nodes and do dfs, we will skip any nodes that we already visited.