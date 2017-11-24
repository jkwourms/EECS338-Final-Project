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

void *chef();

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
	int sockfd, newsockfd, portnum;
	socklen_t custlen;
	char buffer[BUFFER_SIZE];
	struct sockaddr_in serv_addr, cust_addr;
	int order;
	pthread_t tid;

	if (argc < 2) {
		fprintf(stderr, "ERROR: did not provide port number");
		exit(1);
	}
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
	listen(sockfd, 5);
	custlen = sizeof(cust_addr);
	newsockfd = accept(sockfd, (struct sockaddr *) &cust_addr, &custlen);
	if (newsockfd < 0)
		error("ERROR: accept");
	bzero(buffer, BUFFER_SIZE);

	//continue to read orders until number of customers is 0
	
	pthread_create(&tid, NULL, chef, NULL); //launch chef thread
	
	close(newsockfd);
	close(sockfd);
	pthread_join(tid, NULL);
	return 0;
}

void *chef() {
	
	order = read(newsockfd, buffer, BUFFER_SIZE-1);
        if (order < 0)
                error("ERROR: reading from socket");
	
	printf("Your order was : %s\n", buffer);
	order = write(newsockfd, "I got your order", 16);
	if (order < 0)
		error("ERROR: writing to socket");
	if (strcmp(order, "cheese")) {
		printf("sleeping...")
		sleep(2);
		printf("awake!");
	}
	pthread_exit(0);

}
