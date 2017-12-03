/*
    C socket server example, handles multiple clients using threads
    Compile
    gcc server.c -lpthread -o server
*/
 
#include<stdio.h>
#include<string.h>    
#include<stdlib.h>    
#include<sys/socket.h>
#include<arpa/inet.h> 
#include<unistd.h>    
#include<pthread.h> 
 
//the thread function
void *connection_handler(void *);
 
int main(int argc , char *argv[])
{
    int socket_desc , client_sock , c;
    struct sockaddr_in server , client;
     
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
     
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8000 );
     
    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");
     
    //Listen
    listen(socket_desc , 3);
     
    //Accept and incoming connection
    puts("Waiting for hungry customers...");
    c = sizeof(struct sockaddr_in);
    pthread_t thread_id;
    
    while( (client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
    {
        puts("Connection accepted");
         
        if( pthread_create( &thread_id , NULL ,  connection_handler , (void*) &client_sock) < 0)
        {
            perror("could not create thread");
            return 1;
        }
         
        //Now join the thread , so that we dont terminate before the thread
        //pthread_join( thread_id , NULL);
        puts("Handler assigned");
    }
     
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
void *connection_handler(void *socket_desc)
{
    //Get the socket descriptor
    int sock = *(int*)socket_desc;
    int read_size;
    char *message , client_message[2000], *toppings, *invalid;
    char all_orders[5000];
    int order_number = 1;
    
    //toppings = "Topping choices are: banana, apple, granola, strawberry \n"; 
    //write(sock, toppings, strlen(toppings));
     
    //Receive a message from client
    while( (read_size = recv(sock , client_message , 2000 , 0)) > 0 )
    {
        if(strcmp(client_message, "blueberries\n") == 0){

            //end of string marker
            client_message[read_size] = '\0';
            
            //Send the message back to client
            write(sock , client_message , strlen(client_message));
            
            //Write the order and the order number to the buffer
            sprintf(all_orders + strlen(all_orders), "Order #%d: %s", order_number, client_message);

            //clear the message buffer
            memset(client_message, 0, 2000);

            sleep(1);
        }
        else if(strcmp(client_message, "banana\n") == 0){
            //end of string marker
            client_message[read_size] = '\0';
            
            //Send the message back to client
            write(sock , client_message , strlen(client_message));
            
            //Write the order and the order number to the buffer
            sprintf(all_orders + strlen(all_orders), "Order #%d: %s", order_number, client_message);

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
            sprintf(all_orders + strlen(all_orders), "Order #%d: %s", order_number, client_message);

            //clear the message buffer
            memset(client_message, 0, 2000);

            sleep(1);
        }
        else if(strcmp(client_message, "granola\n") == 0){
            //end of string marker
            client_message[read_size] = '\0';
            
            //Send the message back to client
            write(sock , client_message , strlen(client_message));
            
            //Write the order and the order number to the buffer
            sprintf(all_orders + strlen(all_orders), "Order #%d: %s", order_number, client_message);

            //clear the message buffer
            memset(client_message, 0, 2000);

            sleep(1);
        }
        else if(strcmp(client_message, "strawberry\n") == 0){
            //end of string marker
            client_message[read_size] = '\0';
            
            //Send the message back to client
            write(sock , client_message , strlen(client_message));
            
            //Write the order and the order number to the buffer
            sprintf(all_orders + strlen(all_orders), "Order #%d: %s", order_number, client_message);

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
        //write(sock, all_orders, strlen(all_orders));
        printf("%s \n", all_orders);
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }
         
    return 0;
} 
