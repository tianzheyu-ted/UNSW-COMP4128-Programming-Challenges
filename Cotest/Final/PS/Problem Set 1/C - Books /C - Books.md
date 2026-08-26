## C - Books
### Process
The question gives a sequence of estimated time that the boy need to read those books. And the question gives the free time the person has. The output should be the maximum number of book he can read in the order of the sequence.

Since the person will always reading in that order, we can maintain a sliding window, i.e. if the time left is lager than the time needed for the next book, we will add the book into the windows, if not then we will try to remove the book in the front of the window to add the time left back and possiblely have the enough time to read the next book.

### Challenges and Overcoming
The thing I forgot and debug is that after finishing travsing all books, I still need to update the max window size if the current windows size is larger.