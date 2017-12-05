# EECS338-Final-Project

Ok so Chris had some major edits:
"To make it more intuitive, please design it as follows: Customers are client processes that give different orders (different ingredient
requests) to a server. The server launches a separate thread that's a chef, while continuing to take orders. The chef takes time to
prepare each order (different times for different ingredients). When the server finally quits, it prints a log of all the orders."

# Tasks to do
* Need to add a conditional statement to launch NEW thread each time the client submits 
an order request
* Print a message back to customer saying their order is ready (print actual menu order name + order #)

# Final Steps!

* Format the output so it looks nice
* Print out the thread ID of the chef that processed the order
* Have a set number defined in the server so that after X number of client connections to
the socket it says something like "restaurant is now closed" and closes the connection.

 
 
