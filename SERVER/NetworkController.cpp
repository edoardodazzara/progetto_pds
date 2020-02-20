//
// Created by Lorenzo Del Sordo on 2020-01-15.
//

#include <mach/boolean.h>

#include "NetworkController.h"
NetworkController::NetworkController() {
    for (auto i = 0; i < MAX_CLIENT; i++){
        clientSockets[i] = 0;
    }
    if ((masterSocket = socket(AF_INET,SOCK_STREAM,0))==0){
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
}

int NetworkController::serverSide() {
    int master_socket = this->masterSocket;
    int opt = TRUE;
    int addrlen;
    struct sockaddr_in address;
    fd_set readfds;
    int max_sd, sd, activity,new_socket, valRead;

    if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
                   sizeof(opt)) < 0 )
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    //type of socket created
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    //bind the socket to localhost port 8888
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    printf("Listener on port %d \n", PORT);

    //try to specify maximum of 3 pending connections for the master socket
    if (listen(master_socket, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    //accept the incoming connection
    addrlen = sizeof(address);
    puts("Waiting for connections ...");

    while(TRUE)
    {
        //clear the socket set
        FD_ZERO(&readfds);

        //add master socket to set
        FD_SET(master_socket, &readfds);
        max_sd = master_socket;

        //add child sockets to set
        for (auto i = 0 ; i < MAX_CLIENT ; i++)
        {
            //socket descriptor
            sd = this->clientSockets[i];

            //if valid socket descriptor then add to read list
            if(sd > 0)
                FD_SET( sd , &readfds);

            //highest file descriptor number, need it for the select function
            if(sd > max_sd)
                max_sd = sd;
        }

        //wait for an activity on one of the sockets , timeout is NULL ,
        //so wait indefinitely
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);

        if ((activity < 0) && (errno!=EINTR))
        {
            printf("select error");
        }

        //If something happened on the master socket ,
        //then its an incoming connection
        if (FD_ISSET(master_socket, &readfds))
        {
            if ((new_socket = accept(master_socket,
                                     (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
            {
                perror("accept");
                exit(EXIT_FAILURE);
            }

            //add new socket to array of sockets
            for (auto i = 0; i < MAX_CLIENT; i++)
            {
                //if position is empty
                if( clientSockets[i] == 0 )
                {
                    clientSockets[i] = new_socket;
                    printf("Adding to list of sockets as %d\n" , i);

                    break;
                }
            }
        }

        //else its some IO operation on some other socket
        for (auto i = 0; i < MAX_CLIENT; i++)
        {
            sd = clientSockets[i];

            if (FD_ISSET( sd , &readfds))
            {
                //Check if it was for closing , and also read the
                //incoming message
                if ((valRead = read( sd , buffer, 1024)) == 0)
                {
                    //Somebody disconnected , get his details and print
                    getpeername(sd , (struct sockaddr*)&address , \
                        (socklen_t*)&addrlen);
                    printf("Host disconnected , ip %s , port %d \n" ,
                           inet_ntoa(address.sin_addr) , ntohs(address.sin_port));

                    //Close the socket and mark as 0 in list for reuse
                    close( sd );
                    clientSockets[i] = 0;
                }

                    //Echo back the message that came in
                else
                {
                    //set the string terminating NULL byte on the end
                    //of the data read
                    buffer[valRead] = '\0';

                    //ADDING FUNCTIONS HERE
                    //CONTROLLO DELLA STRINGA, CONTROLLO CREDENZIALI, INOLTRO MESSAGGI PER INSERIMENTO O CANCELLAZIONE
                    //set the string terminating NULL byte on the end
                    //of the data read
                    send(sd , buffer , strlen(buffer) , 0 );

                }
            }
        }
    }

    return 0;

}

int NetworkController::clientSide() {
    int sock = this->masterSocket;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    char *hello = "Hello from client";
    int valread;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    send(sock , hello , strlen(hello) , 0 );
    printf("Hello message sent\n");
    valread = read( sock , buffer, 1024);
    printf("%s\n",buffer );
    return 0;
}