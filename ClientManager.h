//
// Created by eli goodwin on 2/9/18.
//

#ifndef CLIENTSERVER_CLIENTMANAGER_H
#define CLIENTSERVER_CLIENTMANAGER_H

#include <thread>
#include <iostream>
#include <queue>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <thread>
#include "RingBuffer.h"

const int BUFFER_SIZE = 500;
class ClientManager {
public:
    ClientManager(std::string targethostName, int targetHostPort, RingBuffer* ringBuffer);
    void sendMessage(std::string message);
    std::string receiveMessage();
    void endConnection();

    void incomingListener();
    void killListener();

private:
    RingBuffer* ringBuffer;
    //targethost port for socket
    int targetHostPort;
    //current host socket
    struct sockaddr_in serverAddress;
    struct hostent* serverHostInfo;
    int socketFD;
    bool killWorkerThread ;
    //connection buffer
    char buffer[BUFFER_SIZE];
    bool createSocket();
    bool connectToTargetHost();
};

#endif //CLIENTSERVER_CLIENTMANAGER_H
