# EECS338-Final-Project

Ok so Chris had some major edits:
"To make it more intuitive, please design it as follows: Customers are client processes that give different orders (different ingredient
requests) to a server. The server launches a separate thread that's a chef, while continuing to take orders. The chef takes time to
prepare each order (different times for different ingredients). When the server finally quits, it prints a log of all the orders."

# Tasks to do
* Print out all menu options for customers to choose from (in client)
* Associate a sleep value with each ingredient item in menu option (in server)
* Server launches a chef thread & sleeps depending on ingredient
* Print a message back to customer saying their order is ready (print actual menu order name
+ order #)
* Save order in another buffer (in server)
* Print out log of orders after last customer receives their food (from new buffer)

