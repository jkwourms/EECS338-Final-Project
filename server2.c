/* server */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#define BUFFER_SIZE 256

void *chef(void *);

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
	int sockfd, newsockfd, portnum;
	char buffer[BUFFER_SIZE];
	char all_orders[BUFFER_SIZE];
	socklen_t custlen;
	struct sockaddr_in serv_addr, cust_addr;
	pthread_t tid;
	if (argc < 2) {
		fprintf(stderr, "ERROR: did not provide port number");
		exit(1);
	}

	//Create Socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("ERROR: opening socket");
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portnum = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portnum);
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		error("ERROR: binding");

	//Listen for connection
	listen(sockfd, 5);
	custlen = sizeof(cust_addr);

	//Accept connection
	while (newsockfd = accept(sockfd, (struct sockaddr *) &cust_addr, &custlen)) {
		if (pthread_create(&tid, NULL, chef, &newsockfd) < 0)
			error("ERROR: could not create thread");
	}

	//Close sockets & join threads
	close(newsockfd);
	close(sockfd);
	pthread_join(tid, NULL);
	return 0;
}

void *chef(void *sockfd) {
	char total_order_buffer[BUFFER_SIZE];

	//Get socket descriptor
	int orderNumber;
	int sock = *(int*)sockfd;
	int read_size;
	char *order, customer_order[100];
	const char *toppings[5];

	//Send message to the customer
	toppings[0] = "Blueberries";
	toppings[1] = "Strawberries";
	toppings[2] = "Granola";
	toppings[3] = "Coconut shavings";
	toppings[4] = "Banana";
	write(sock, toppings, 6);
	order = "Please choose your toppings: ";
	write(sock, order, strlen(order));

	//Receive message from customer
	while ((read_size = recv(sock, customer_order, 100, 0)) > 0) {
		//Read for which topping is ordered
		if (strcmp(customer_order, "Blueberries") == 0) {
			//add time to chef
			sleep(3);
		} 
		else if (strcmp(customer_order, "Strawberries") == 0){
			//add time to chef
			sleep(2);
		}
		else if (strcmp(customer_order, "Granola") == 0){
			//add time to chef
			sleep(2);
		}
		else if (strcmp(customer_order, "Coconut shavings") == 0){
			//add time to chef
			sleep(10);
		}
		else if (strcmp(customer_order, "Banana") == 0){
			//add time to chef
			sleep(5);
		}
		else {
			bzero(total_order_buffer, BUFFER_SIZE);
			printf("Please list valid ingredients.");
			fflush(stdout);
		}
		
		orderNumber++;

		//End of string marker
		customer_order[read_size] = '\0';

		//Send message back to customer
		write(sock, orderNumber, strlen(orderNumber));
		write(sock, customer_order, strlen(customer_order));
		//Clear message buffer
		//bzero(buffer, 100)

		sprintf(total_order_buffer, orderNumber + customer_order);
	}

	if (read_size == 0) {
		//print out the customers order from a buffer
		printf(total_order_buffer);

		printf("Thank you, come again!");
		fflush(stdout);
	}

   	close(sock);
	pthread_exit(0);

}
