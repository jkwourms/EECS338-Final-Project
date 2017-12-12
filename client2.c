/* client */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#define BUFFER_SIZE 100

void error(const char *msg) {
    perror(msg);
    exit(0);
}

int main() {
    //int r = (rand() % 5) + 1; 
    int r = 3;
    int sockfd, portnum, order, n, closed;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[BUFFER_SIZE], all_orders[5000];

    //Create socket
    portnum = 8888;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname("127.0.0.1");
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portnum);

    //Connect 
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    
    //Check if server sent message to client
    closed = recv(sockfd, buffer, 1024, 0);
    //Check if restaurant is closed
    if(strcmp(buffer, "closed") == 0){
        //read the message from the server into the buffer
        bzero(buffer, BUFFER_SIZE);
        printf("Restaurant is closed! \n");
        close(sockfd);
    }
    else{
        //Continue placing orders until # of customers is 0
        printf("Welcome to Jenny and Grace's Lit AF Acai Bowl Shop! \n");
        printf("Topping choices are: blueberries, banana, apple, granola, strawberries \n");
        for (int i = 0; i < r; i++) {
            printf("Please choose a topping: ");
            bzero(buffer,BUFFER_SIZE);
            fgets(buffer,BUFFER_SIZE-1,stdin);
            order = write(sockfd,buffer,strlen(buffer));
            if (order < 0) 
                 error("ERROR writing to socket");
            bzero(buffer,BUFFER_SIZE);
            order = read(sockfd,buffer,BUFFER_SIZE-1);
            if (order < 0) 
                 error("ERROR reading from socket");
            printf("%s\n",buffer);
            bzero(buffer, BUFFER_SIZE);
        }
    }

    printf("%s\n", buffer);

    close(sockfd);
    return 0;
}
