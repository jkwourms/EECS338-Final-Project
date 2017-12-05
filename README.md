# EECS338-Final-Project

Ok so Chris had some major edits:
"To make it more intuitive, please design it as follows: Customers are client processes that give different orders (different ingredient
requests) to a server. The server launches a separate thread that's a chef, while continuing to take orders. The chef takes time to
prepare each order (different times for different ingredients). When the server finally quits, it prints a log of all the orders."

# Tasks to do
* Associate a sleep value with each ingredient item in menu option (in server)
* Server launches a chef thread & sleeps depending on ingredient
* Print a message back to customer saying their order is ready (print actual menu order name + order #)

# New Tommy advice

I just got an email back from Tommy about the thread situation if you want to give it a try! 
I'll work on it again another day, but I'll quote it in case you have time to look at it.

> I believe the issue may be that you are using two separate thread array to keep track of the number. That is, you are using a thread[i] for your thread function and thread_num[i] for your main function, so they are separate arrays. Also since you make the thread array, you did not specify any numbers so while the index changes, the contents which have been initialized to some random number has not changed. That means the number is off by whatever it has been initialized to when you really should define the numbers in your array or use the index increment as your tid.

Note that when I talk about tid id, it is simply a way to keep track of how many threads and which thread you are on, this is a simple as keeping a tid variable that increments and is applied to each thread. "

 
