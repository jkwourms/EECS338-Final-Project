/* server */
 
#include<stdio.h>
#include<string.h>    
#include<stdlib.h>    
#include<sys/socket.h>
#include<arpa/inet.h> 
#include<unistd.h>    
#include<pthread.h> 
#define BUFFER_SIZE 100
 

//Global variables
int max_customers = 2;
int client_sock;

//the thread function
void *chef(void *);

//struct
struct order_struct {
    int tid;
    int order_sock;
    int customer;
};
 
int main(int argc , char *argv[])
{
    int socket_desc , client_sock , c;
    struct sockaddr_in server , client;
    pthread_t thread_id[3]; 
    int thread_num = 0;
    char client_message[2000];
    char closed[2000] = "closed";
    struct order_struct args;
    char buffer[BUFFER_SIZE];
    int customer_amount = 0;
 
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
     
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8888 );
     
    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }

    //Listen
    listen(socket_desc , 3);
     
    //Accept and incoming connection
    puts("Waiting for hungry customers...");
    c = sizeof(struct sockaddr_in);
    
    args.customer = 0;



    while((client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)))
    {
        if(customer_amount < max_customers){
            customer_amount++;
            sprintf(buffer, "open");
            send(client_sock,buffer,13,0);
            bzero(buffer, BUFFER_SIZE);

            args.customer++;
            args.order_sock = client_sock;
            args.tid = thread_num + 1;

            //needs to be called everytime the client submits a request
            if( pthread_create( &thread_id[thread_num] , NULL ,  chef , (void*) &args) < 0)
            {
                perror("could not create thread");
                return 1;
            }
            thread_num++;

            //puts("Chef assigned");
            printf("Chef #%d assigned to customer %d\n", args.tid, args.customer);
        }
        else{
            //Tell the client that the restaurant is closed
            printf("Sorry, the kitchen is closing! \n");
            sprintf(buffer, "closed");
            send(client_sock,buffer,13,0);
            shutdown(client_sock, SHUT_WR);
        }

    }
    

    printf("Restaurant closed!\n");
       
    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }
    return 0;
}
 
/*
 * This will handle connection for each client
 * */
void *chef(void *arguments)
{
    struct order_struct *args = arguments;
    int sock = args->order_sock;
    int thread = args->tid;
    int customer_number = args->customer;

    //Get the socket descriptor
    int read_size;
    char *message , client_message[2000], *toppings, *invalid;
    char all_orders[5000];
    int order_number = 1;

    //Receive a message from client
    while( (read_size = recv(sock , client_message , 2000 , 0)) > 0 )
    {
        
        if(strcmp(client_message, "blueberries\n") == 0){

            //end of string marker
            client_message[read_size] = '\0';
            
            //Send the message back to client
            write(sock , client_message , strlen(client_message));
            
            //Write the order and the order number to the buffer
            sprintf(all_orders + strlen(all_orders), "   Ingredient #%d: %s", order_number, client_message);

            //clear the message buffer
            memset(client_message, 0, 2000);

            sleep(2);

        }
        else if(strcmp(client_message, "banana\n") == 0){
            
            //end of string marker
            client_message[read_size] = '\0';
            
            //Send the message back to client
            write(sock , client_message , strlen(client_message));
            
            //Write the order and the order number to the buffer
            sprintf(all_orders + strlen(all_orders), "   Ingredient #%d: %s", order_number, client_message);

            //clear the message buffer
            memset(client_message, 0, 2000);

            sleep(1);

        }
        else if(strcmp(client_message, "apple\n") == 0){
            //end of string marker
            client_message[read_size] = '\0';
            
            //Send the message back to client
            write(sock , client_message , strlen(client_message));
            
            //Write the order and the order number to the buffer
            sprintf(all_orders + strlen(all_orders), "   Ingredient #%d: %s", order_number, client_message);

            //clear the message buffer
            memset(client_message, 0, 2000);

            sleep(4);

        }
        else if(strcmp(client_message, "granola\n") == 0){
            //end of string marker
            client_message[read_size] = '\0';
            
            //Send the message back to client
            write(sock , client_message , strlen(client_message));
            
            //Write the order and the order number to the buffer
            sprintf(all_orders + strlen(all_orders), "   Ingredient #%d: %s", order_number, client_message);

            //clear the message buffer
            memset(client_message, 0, 2000);

            sleep(5);

        }
        else if(strcmp(client_message, "strawberries\n") == 0){
            //end of string marker
            client_message[read_size] = '\0';
            
            //Send the message back to client
            write(sock , client_message , strlen(client_message));
            
            //Write the order and the order number to the buffer
            sprintf(all_orders + strlen(all_orders), "   Ingredient #%d: %s", order_number, client_message);

            //clear the message buffer
            memset(client_message, 0, 2000);

            sleep(1);

        }
        else{
            invalid = "That's not an option, next! \n";
            write(sock, invalid, strlen(invalid));
            memset(client_message, 0, 2000);
        }
        order_number++;
    }
     
    if(read_size == 0)
    {
        printf("Chef #%d has finished customer %d's order of:\n%s \n", thread, customer_number, all_orders);
        printf("Customer %d left\n", customer_number);
        max_customers--;
        if(max_customers == 0){
            exit(0);
            return 0;
        }
        fflush(stdout);
        pthread_exit(0);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }
         
    return 0;
} 
