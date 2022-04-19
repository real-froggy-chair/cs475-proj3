# cs475-proj3

Xinu Project 3
https://davidtchiu.github.io/teaching/cs475/proj3/

A program that emulates the Dining Philosopher problem, using XINU. We coded: 
- A custom, atomic spin-lock and unlock
- Commented on assembly code for lock_and_test used in the spin-lock
- Created a dynamic locking interface for philosophers wherein one process seeks to have both a left and right "fork" out of a pool of N forks
-- Note threads are only allowed to access forks immediately adjacent (philosopher 2 can only access fork 2 and fork 1, for example).
-- We seize the left fork without checking, then, once it's secured, we check to see if the right fork is available. If it isn't we release the left, otherwise, we eat().
- Excessive locks are included to prevent unintended context switching (printLock)

I have no idea what to write in a README so I hope you're just checking this to see if we wrote anything.

If you do read these all the way through please leave a smiley face in our comments on the grade :)