/* server */
 
#include<stdio.h>
#include<string.h>    
#include<stdlib.h>    
#include<sys/socket.h>
#include<arpa/inet.h> 
#include<unistd.h>    
#include<pthread.h> 
 
//the thread function
void *chef(void *);

//struct
struct order_struct {
    pthread_t tid[3]; 
    int order_sock;
};
 
int main(int argc , char *argv[])
{
    int socket_desc , client_sock , c;
    struct sockaddr_in server , client;
    pthread_t thread_id[3]; 
    int thread_num = 0;
    char client_message[2000];
    struct order_struct args;
     
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
    server.sin_port = htons( 8888 );
     
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
    
    while( (client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
    {
        puts("Connection accepted");
        args.order_sock = client_sock;
        args.tid[thread_num] = thread_id[thread_num];
         
        //needs to be called everytime the client submits a request
        if( pthread_create( &thread_id[thread_num] , NULL ,  chef , (void*) &args) < 0)
        {
            perror("could not create thread");
            return 1;
        }
        thread_num++;
        //printf("thread_num : %d\n", thread_num);
        //sleep(2);

        puts("Chef assigned");
    }
     
    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }

    close(client_sock);

    return 0;
}
 
/*
 * This will handle connection for each client
 * */
void *chef(void *arguments)
{

    struct order_struct *args = arguments;
    int sock = args->order_sock;
    int thread = *(int*)args->tid;

    //Get the socket descriptor
    //int sock = *(int*)socket_desc;
    int read_size;
    char *message , client_message[2000], *toppings, *invalid;
    char all_orders[5000];
    int order_number = 1;
    
    //toppings = "Topping choices are: banana, apple, granola, strawberry \n"; 
    //write(sock, toppings, strlen(toppings));
     
    //Receive a message from client
    while( (read_size = recv(sock , client_message , 2000 , 0)) > 0 )
    {
        //printf("THREAD LAUNCHED : %d\n", thread);
        //fflush(stdout);
        
        if(strcmp(client_message, "blueberries\n") == 0){

            //end of string marker
            client_message[read_size] = '\0';
            
            //Send the message back to client
            write(sock , client_message , strlen(client_message));
            
            //Write the order and the order number to the buffer
            sprintf(all_orders + strlen(all_orders), "Order #%d: %s", order_number, client_message);

            //clear the message buffer
            memset(client_message, 0, 2000);

            sleep(2);

            //print when finished
            printf("Chef has finished preparing order #%d!\n", order_number);
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

            //print when finished
            printf("Chef #%d has finished preparing order #%d!\n", thread, order_number);
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

            sleep(4);

            //print when finished
            printf("Chef #%d has finished preparing order #%d!\n", thread, order_number);
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

            sleep(5);

            //print when finished
            printf("Chef #%d has finished preparing order #%d!\n", thread, order_number);
        }
        else if(strcmp(client_message, "strawberries\n") == 0){
            //end of string marker
            client_message[read_size] = '\0';
            
            //Send the message back to client
            write(sock , client_message , strlen(client_message));
            
            //Write the order and the order number to the buffer
            sprintf(all_orders + strlen(all_orders), "Order #%d: %s", order_number, client_message);

            //clear the message buffer
            memset(client_message, 0, 2000);

            sleep(1);

            //print when finished
            printf("Chef #%d has finished preparing order #%d!\n", thread, order_number);
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
        printf("%s \n", all_orders);
        puts("Client disconnected");
        fflush(stdout);
        //not exiting?
        close(sock);
        pthread_exit(0);
        return 0;
    }
    else if(read_size == -1)
    {
        perror("recv failed");
    }
         
    return 0;
} 
