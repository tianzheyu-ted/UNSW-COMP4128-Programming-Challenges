# Problem Set 9

## B. Pair Of Lines

![](submission.png)

### Process
At least two of any 3 points must lie on one of the two lines. I wrote a helper function to collect all points not on this assumed first line, and then checked if all the remaining points were collinear to form a valid second line.

### Challenges and Overcoming
When coding the loop to verify the remaining points for the second line, I ran into a logic bug where I checked their collinearity against the points from the first line (`A`, `B`) instead of the base points for the second line (`C`, `D`). I found it when my submission failed on Test 8 with a wrong answer, outputting `NO` instead of `YES`. Because the first three points in that test were collinear, my loop was incorrectly rejecting the valid points on the second line. Next time to prevent this bug, I will carefully trace my variable references inside loops, especially when managing multiple sets of similar variables (like two pairs of line coordinates), to ensure I am validating against the correct baseline.
