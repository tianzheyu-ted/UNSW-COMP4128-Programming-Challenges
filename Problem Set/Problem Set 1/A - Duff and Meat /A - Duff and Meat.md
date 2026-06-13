## A - Duff and Meat
### Process
The question is asking to minimized the money needed to buy meat. Since we are allow to keep the meat we perivously bought to meet her future requirement, the nature thought is to buy all the meat needed in the day when the price is lowest. So we can sort the price, and try to buy all the meat in that day.

### Challenges and Overcoming
However, for example there are day1 and day2, and the price of meat in day2 is lower than day1, in this case we can not buy meat in day2 to meet the requirement in day1. This tells us we can only buy the meat to satisfy dayX's requirement in the lowest price day that before dayX.


This means when we are traversing all the day, we need to somehow know the lowest price day before it. The naive way is to traverse all the day before it to get the lowest price, however we can do better by keeping the lowest price before that day and update it if the current price is lower. This reduce the time complexity from O(n^2) to O(n).