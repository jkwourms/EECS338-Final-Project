#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#define BUFFER_SIZE 256

void error(const char *msg) {
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[]) {
    int sockfd, portnum, order;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[BUFFER_SIZE];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portnum = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
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
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    
    //continue asking for orders until # of customers is 0
    for (int i = 0; i < 2; i++) {
        printf("Please enter your order: ");
        //bzero(buffer,BUFFER_SIZE);
        fgets(buffer,BUFFER_SIZE-1,stdin);
        order = write(sockfd,buffer,strlen(buffer));
        if (order < 0) 
             error("ERROR writing to socket");
        //bzero(buffer,BUFFER_SIZE);
        order = read(sockfd,buffer,BUFFER_SIZE-1);
        if (order < 0) 
             error("ERROR reading from socket");
        printf("%s\n",buffer);
    }
    
    close(sockfd);
    return 0;
}
