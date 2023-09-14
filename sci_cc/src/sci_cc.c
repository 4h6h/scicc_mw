#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <mqueue.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/time.h>
#include <netinet/in.h>

#include "std_types.h"
#include "log.h"

#include "sci_cc.h"
#include "sci_cc_Cfg.h"
#include "sci_cc_call.h"

#include "mw_queue_types.h"

/* Due to the fact that we program linux sockets, we need to cope with the signature 
   of the respective functions, that uses int excessively */

/* Forward declaration of *_Lcfg.c, all const */
_PUBLIC char_t *STANDARD_MESSAGE;

/* Module local variables */
_PRIVATE uint16_t client_socket[MAX_CLIENTS] = {0}; /* initialize all client_sockets to 0, so not checked */
_PRIVATE uint16_t server_socket = 0;
_PRIVATE struct sockaddr_in address;
_PRIVATE size_t addrlen = sizeof(address);
_PRIVATE fd_set readfds; /* set of socket descriptors */
_PRIVATE uint16_t fd_q = 0; 

_PUBLIC void sci_cc_init(uint16_t _fd_q)
{   
    int opt = 1;
    fd_q = _fd_q;

    /* type of sockets to be created */
    address.sin_family = AF_INET;  
    address.sin_addr.s_addr = INADDR_ANY;  
    address.sin_port = htons( PORT );  

    /* create a server/master socket */
    if ( (server_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    /* set server socket to allow multiple connections */
    if ( setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (char_t *)&opt, sizeof(opt)) < 0 )
    {
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }

    /* bind the socket to port */
    if ( bind(server_socket, (struct sockaddr *)&address, sizeof(address)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    /* try to specify max_pending_connections for the server socket */
    if ( listen(server_socket, MAX_PENDING_CONS) < 0)
    {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

}

_PRIVATE void serve_server(void)
{
    uint16_t iter = 0; /* iterator for */
    int16_t new_socket = accept(server_socket, (struct sockaddr *)&address, (socklen_t *)&addrlen);

    if (new_socket < 0)
    {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }

    /* send welcome message */
    size_t len_message = strlen(STANDARD_MESSAGE);
    size_t len_sent = send(new_socket, STANDARD_MESSAGE, len_message, 0);
    if ( len_sent != len_message )
    {
        perror("send went wrong");
    }

    /* add new socket to the list */
    for (iter = 0; iter < MAX_CLIENTS; iter++)  
    {   
        if( client_socket[iter] == 0 )  
        {  
            client_socket[iter] = new_socket;  
            printf("Adding to list of sockets as %d\n" , iter);               
            break;  
        }
    }
}

_PRIVATE void serve_clients(void)
{
    uint16_t iter = 0; /* iterator for */
    uint16_t sd = 0;
    uint16_t read_size = 0;
    char_t buffer[READ_BUFFER_LENGTH] = {0};

    for (iter=0; iter < MAX_CLIENTS; iter++)
    {
        sd = client_socket[iter];

        if ( FD_ISSET(sd, &readfds) == true )
        {
            read_size = read(sd, buffer, READ_BUFFER_LENGTH);

            if (read_size == 0)
            {
                /* disconnected connection */
                getpeername(sd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
                close(sd);
                client_socket[iter] = 0;
            } 
            else 
            {
                ipc_message_t message;
                message.type = LST;
                memcpy(message.payload, buffer, sizeof(message.payload));

                mw_sci_cc_send(&message); /* required if of mw */
            }
        }
    }
}

_PRIVATE void serve_ipc(void)
{
    uint16_t iter = 0; /* iterator in for */
    uint16_t sd = 0;
    ipc_message_t message = {
        .type = 0,
        .payload = {0},
    };
    
    mw_sci_cc_receive(&message);  /* required if mw_sci_cc_receive of mw */
    
    for (iter=0; iter<MAX_CLIENTS; iter++)
    {
        sd = client_socket[iter];
        if (sd > 0) 
        {
            if( send(sd, (const char *)&message, sizeof(message), 0) < 0 )  
            {  
                perror("send ipc");  
            }  
        }
    }
}

_PUBLIC void sci_cc_event_loop(void)
{
    uint16_t iter = 0; /* iterator in for */
    uint16_t max_sd = 0; 
    uint16_t sd = 0;
    int64_t activity; 

    /* clear socket set */
    FD_ZERO(&readfds);

    /* add queue fd to descriptor list */
    FD_SET(fd_q, &readfds);

    /* add the server socket to the descriptor set */
    FD_SET(server_socket, &readfds);
    max_sd = server_socket;

    /* add client sockets to the descriptor set */
    for (iter=0; iter<MAX_CLIENTS; iter++)
    {
        sd = client_socket[iter];
        if (sd > 0) FD_SET(sd, &readfds);
        max_sd = (sd > max_sd) ? sd : max_sd;
    }

    /* wait for an activity */
    activity = select(max_sd+1, &readfds, NULL, NULL, NULL);

    if ((activity<0) && (errno!=EINTR))
    {
        perror("select error");
        exit(EXIT_FAILURE);
    }

    if ( FD_ISSET(server_socket, &readfds) )
    {
        serve_server();
    } 
    else if ( FD_ISSET(fd_q, &readfds) )
    {
        serve_ipc();
    }
    else
    {
        serve_clients();
    } 
}