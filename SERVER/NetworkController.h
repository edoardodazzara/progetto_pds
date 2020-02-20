//
// Created by Lorenzo Del Sordo on 2020-01-15.
//

#ifndef PROGETTO_NETWORKCONTROLLER_H
#define PROGETTO_NETWORKCONTROLLER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <map>
#include <vector>
#include <iostream>
#define PORT 8080
#define MAX_CLIENT 5


class NetworkController {
    int masterSocket;
    char buffer[1024];
    int clientSockets[MAX_CLIENT];


public:
    NetworkController();

    int serverSide();
    int clientSide();

};


#endif //PROGETTO_NETWORKCONTROLLER_H
