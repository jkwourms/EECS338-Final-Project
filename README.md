# EECS338-Final-Project

Ok so Chris had some major edits:
"To make it more intuitive, please design it as follows: Customers are client processes that give different orders (different ingredient
requests) to a server. The server launches a separate thread that's a chef, while continuing to take orders. The chef takes time to
prepare each order (different times for different ingredients). When the server finally quits, it prints a log of all the orders."

# So...
* Making a server/client program now
* Customers are clients that submit menu requests w/ different ingredients
* Server launches a chef thread that takes time depending on what ingredients were ordered
* When server quits, it prints a log of all orders
* Also said to make client/server communication socket based, since customers can arrive at any time

# Add...
* fprintf all the options for orders
* change loop to process where a random number of customers arrive & place orders
* chef sleeps depending on order
